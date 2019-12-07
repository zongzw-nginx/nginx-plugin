#!/usr/bin/perl

# (C) Maxim Dounin

# Tests for "proxy_request_buffering off".

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
            proxy_pass http://127.0.0.1:8080/catch;
            proxy_request_buffering off;
            add_header X-Request-Time $request_time always;
        }

        location /catch {
            proxy_pass http://127.0.0.1:8080/proxy;
            proxy_request_buffering off;
            catch_body on;
        }

        location /proxy {
            proxy_pass http://127.0.0.1:8080/empty;
            proxy_request_buffering on;
        }

        location /empty {
            return 200 "test response body\n";
        }
    }
}

EOF

$t->write_file('index.html', 'SEE-THIS');
$t->try_run('no catch_body')->plan(1);

###############################################################################

# buffering switched off - expect immediate reject,
# before we'll send second part of the body

like(get_sleep('/', '12345X', '123456'),
	qr/403 Forbidden.*X-Request-Time: 0/ms,
	'unbuffered request rejected');

###############################################################################

sub get_sleep {
	my $uri = shift;
	my $first = shift;
	my $second = shift;
	my $length = length($first) + length($second);
	return http(
		"GET $uri HTTP/1.1" . CRLF
		. "Host: localhost" . CRLF
		. "Connection: close" . CRLF
		. "Content-Length: $length" . CRLF . CRLF
		. $first,
		sleep => 1.1,
		body => $second
	);
}

###############################################################################
