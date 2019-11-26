var c = require('crypto');
function md5(data) {

    let hash = c.createHash('md5');
    return hash.update(data).digest('hex');
}



function run_md5_n_times_with_timer(num) {
    let st = new Date().getTime();
    let fin = '';
    let n = 0;
    let ns = '';
    for(; n<num; n+=1) {
        ns = `${n}`;
        fin = md5(ns);
    }
    let et = new Date().getTime();
    console.log(`${fin}: ${ns}, tv:${(et-st)} millisecs`);
}

if(process.argv.length !== 3) {
    console.log(`<num>`);
    process.exit(1)
}
run_md5_n_times_with_timer(Number(process.argv[2]));