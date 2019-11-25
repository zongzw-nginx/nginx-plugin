#!/bin/bash 

if [ $# -ne 1 ]; then 
    echo "$0 <times>"; 
    exit 1;
fi
times=$1

fmtstr="%-20s %15s %15s\n"

function run_and_analyze() {
    cmd=$1

    sum=0
    i=0;
    while [ $i -lt $times ]; do
        out=`$cmd`
        cost=`echo $out | sed 's/.* tv://' | sed 's/ millisecs//'`
        sum=$((sum + $cost))
        i=$((i+1))
    done
    
    printf "$fmtstr" "\"$cmd\"" "$sum" "$(($sum / $times))"
}

printf "$fmtstr" "Command" "Total Time" "Average Time"

run_and_analyze "./md5 10000"
run_and_analyze "node md5.js 10000"
run_and_analyze "lua md5.lua 10000"