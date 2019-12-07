#!/usr/bin/perl

# (C) Maxim Dounin

# Tests for catch body filter module.

###############################################################################

use warnings;
use strict;

use Test::More;
use Test::Nginx;

use Socket qw/ CRLF /;

###############################################################################

select STDERR; $| = 1;
select STDOUT; $| = 1;

my $t = Test::Nginx->new()->has(qw/http proxy rewrite/)
	->write_file_expand('nginx.conf', <<'EOF');

%%TEST_GLOBALS%%

daemon off;

events {
}

http {
    %%TEST_GLOBALS_HTTP%%

    server {
        listen       127.0.0.1:8080;
        server_name  localhost;
        location / {
            catch_body on;
            proxy_pass http://127.0.0.1:8080/empty;
        }
        location /empty {
            return 200 "test response body\n";
        }
    }
}

EOF

$t->write_file('index.html', 'SEE-THIS');
$t->try_run('no catch_body')->plan(6);

###############################################################################

like(get_body('/', '123456'), qr/200 OK/, 'normal');
like(get_body('/', '12345X'), qr/403 Forbidden/, 'rejected');

# pipelining

like(get_body('/', '123456', '12345X'),
	qr/200 OK.*403 Forbidden/ms,
	'second rejected');

like(get_body('/', '123456' x 1024, '12345X6789' x 1024, '123456' x 1024),
	qr/200 OK.*403 Forbidden(?!.*400 Bad)/ms,
	'accepted rejected ignored');

# pipelining with chunked

like(get_chunked('/', '123456', '12345X'),
	qr/200 OK.*403 Forbidden/ms,
	'chunked second rejected');

like(get_chunked('/', '123456', '12345X6789', '123456'),
	qr/200 OK.*403 Forbidden(?!.*400 Bad)/ms,
	'chunked accepted rejected ignored');

###############################################################################

sub get_body {
	my $uri = shift;
	my $last = pop;
	return http( join '', (map {
		my $body = $_;
		"GET $uri HTTP/1.1" . CRLF
		. "Host: localhost" . CRLF
		. "Content-Length: " . (length $body) . CRLF . CRLF
		. $body
	} @_),
		"GET $uri HTTP/1.1" . CRLF
		. "Host: localhost" . CRLF
		. "Connection: close" . CRLF
		. "Content-Length: " . (length $last) . CRLF . CRLF
		. $last
	);
}

sub get_chunked {
	my $uri = shift;
	my $last = pop;
	return http( join '', (map {
		my $body = $_;
		"GET $uri HTTP/1.1" . CRLF
		. "Host: localhost" . CRLF
		. "Transfer-Encoding: chunked" . CRLF . CRLF
		. sprintf("%x", length $body) . CRLF
		. $body . CRLF
		. "0" . CRLF . CRLF
	} @_),
		"GET $uri HTTP/1.1" . CRLF
		. "Host: localhost" . CRLF
		. "Connection: close" . CRLF
		. "Transfer-Encoding: chunked" . CRLF . CRLF
		. sprintf("%x", length $last) . CRLF
		. $last . CRLF
		. "0" . CRLF . CRLF
	);
}

###############################################################################
