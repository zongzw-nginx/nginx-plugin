#!/bin/bash 

cdir=`cd $(dirname $0); pwd`

bindir=$cdir/../src/nginx-1.16.1/objs

ps -ef | grep -v grep | grep "nginx: master process"
if [ $? -ne 0 ]; then 
    $bindir/nginx
fi

$bindir/nginx -s reload 
sleep 1

ps -ef | grep -v grep | grep "nginx: worker process"
if [ $? -ne 0 ]; then 
    echo "nginx worker process not found.";
    exit 1;
fi

pid=`ps -ef | grep -v grep | grep "nginx: worker process" | tr -s ' ' | cut -d ' ' -f2`

gdb -p $pid
