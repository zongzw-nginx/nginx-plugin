function moduleTest(res) {
    res.return(200, "The njs module was loaded.\n");
}


var c = require('crypto');
function md5(data) {

    var hash = c.createHash('md5');
    return hash.update(data).digest('hex');
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
    // console.log(`${fin}: ${ns}, tv:${(et-st)*1000} millisecs`); 
    return `${fin}: ${ns}, tv:${(et-st)*1000} millisecs`;
}

function start(r) {
    r.status = 200; 
    r.sendHeader();
    r.send(run_md5_n_times_with_timer(r.variables.mynum));
    r.finish();
} 