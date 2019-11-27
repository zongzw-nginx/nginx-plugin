#!/bin/bash 

export HOMEDIR=`cd $(dirname $0); pwd`/..

docker-compose -f $HOMEDIR/scripts/docker-compose.yml \
    up -d --force-recreate

docker exec NGINX \
    forever start /root/ngx-deps-app/dist/main.js

echo -n "Waiting for nestjs startup "
i=0;
while [ $i -lt 20 ]; do 
    echo -n .
    s=`curl http://localhost:81/remotemd5/1 -w "%{http_code}" -s -o /dev/null`
    if [ "$s" = '200' ]; then break; 
    elif [ $i -ge 10 ]; then echo "nestjs timeout"; fi
    sleep 1
done
echo 