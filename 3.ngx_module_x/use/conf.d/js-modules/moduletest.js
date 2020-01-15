var c = require('crypto');

function moduleTest(res) {
    res.return(200, "The njs module was loaded.\n");
}

function md5(data) {

    var hash = c.createHash('md5');
    return hash.update(data).digest('hex');
}

function foxfox_len(r) {
    function calc_len(res) {
        r.error(`${res.status}, ${res.responseBody}`);
        r.return(res.status, `${res.responseBody.length}`);
    }

    r.subrequest(
        '/fox_internal_uri', 
        {
            args: '',
            method: 'GET',
            body: JSON.stringify({})
        },
        calc_len
    )
}

function run_md5_n_times_with_timer(num) {
    var st = new Date().getTime();
    var fin = '';
    var n = 0;
    var ns = '';
    for(; n<num; n+=1) {
        ns = `${n}`;
        fin = md5(ns);
    }
    var et = new Date().getTime();
    // *35 js exception: ReferenceError: "console" is not defined in moduletest.js:23
    // console.log(`${fin}: ${ns}, tv:${(et-st)} millisecs`); 
    return `${fin}: ${ns}, tv:${(et-st)} millisecs`;
}

function localmd5(r) {
    r.status = 200; 
    r.sendHeader();
    r.send(run_md5_n_times_with_timer(r.variables.mynum));
    r.finish();
} 

// var r = require('http');

function remotemd5(r) {
    function done(res) {
        r.return(res.status, res.responseBody);
    }

    r.subrequest(`/localmd5/${r.variables.mynum}`, {
        args: '',
        method: 'GET',
        body: JSON.stringify({})
    }, done);

    // r.finish();
    /**
     * 2019/11/26 06:31:24 [error] 53#53: *14 open() "/etc/nginx/htmlhttp://localhost:3000/md5sum/10000" failed (2: No such file or directory), client: 172.245.18.1, server: localhost, request: "GET /remotemd5/10000 HTTP/1.1", subrequest: "http://localhost:3000/md5sum/10000", host: "localhost:81"
     * 172.245.18.1 - - [26/Nov/2019:06:31:24 +0000] "GET /remotemd5/10000 HTTP/1.1" 500 177 "-" "PostmanRuntime/7.19.0" "-"
     */
    // r.subrequest(`http://localhost:3000/md5sum/${r.variables.mynum}`);


    r.subrequest(`/internal/${r.variables.mynum}`, {
        args: '',
        method: 'GET',
        body: JSON.stringify({})
    }, done);

}

