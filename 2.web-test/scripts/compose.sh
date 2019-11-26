#!/bin/bash 

export HOMEDIR=`cd $(dirname $0); pwd`/..

docker-compose -f $HOMEDIR/scripts/docker-compose.yml up -d --force-recreate

docker exec NGINX forever start ngx-deps-app/dist/main.js

