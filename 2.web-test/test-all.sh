#!/bin/bash 

cdir=`cd $(dirname $0);pwd`
(
    cd $cdir/scripts

    docker ps | grep -oE "(TESTNGX|OPENRESTY)" > /dev/null
    # if [ $? -ne 0 ]; then ./compose.sh; fi
    ./compose.sh
)


fmtstr="%-20s %15s %15s\n"

echo "============ description ============="
echo "Displays the response time(millisecs) of web services who calculate md5(1..10000)"
echo 

echo "run 20 times:"
printf "$fmtstr" "Command" "Total Time" "Average Time"

for task in \
    'http://localhost:81/localmd5/10000   |nginx->njs' \
    'http://localhost:81/remotemd5/10000  |nginx->nodejs' \
    'http://localhost:80/md5sum/10000     |openresty->lua' \
    'http://localhost:81/md5-1.fcgi/10000 |nginx->cgi(1)' \
    'http://localhost:81/md5-2.fcgi/10000 |nginx->cgi(2)'; do 

    url=`echo $task | cut -d ' ' -f 1`
    tnm=`echo $task | cut -d '|' -f 2`
    sum=0
    for n in {1..20}; do 
        tc=`curl -s -w "%{time_total}" $url -o /dev/null`;
        tc=`printf "%.3f" $tc`
        tc=`echo $tc | sed 's/\.//' | sed 's/^0\{1,\}//'`
        sum=$(($sum + $tc))
    done;
    
    printf "$fmtstr" "\"$tnm\"" "$sum" "$(($sum / 20))"
done;

# docker stop TESTNGX OPENRESTY > /dev/null