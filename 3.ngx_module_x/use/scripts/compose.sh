#!/bin/bash 

export HOMEDIR=`cd $(dirname $0); pwd`/..

docker-compose -f $HOMEDIR/scripts/docker-compose.yml \
    up -d --force-recreate

docker exec USENGX make -C /root/src/demo-fcgi
docker exec USENGX spawn-fcgi -p 8081 -f /root/src/demo-fcgi/demo -F 3
