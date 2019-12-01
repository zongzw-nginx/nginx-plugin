#!/bin/bash 

export HOMEDIR=`cd $(dirname $0); pwd`/..

docker-compose -f $HOMEDIR/scripts/docker-compose.yml \
    up -d --force-recreate

docker exec TESTNGX \
    forever start /root/src/ngx-deps-app/dist/main.js

docker exec TESTNGX make -C /root/src/local-fcgi
docker exec TESTNGX spawn-fcgi -p 8081 -f /root/src/local-fcgi/cgi-md5 -F 1
docker exec TESTNGX spawn-fcgi -p 8082 -f /root/src/local-fcgi/cgi-md5 -F 2

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

