#!/bin/bash 

export HOMEDIR=`cd $(dirname $0); pwd`/..

docker-compose -f $HOMEDIR/scripts/docker-compose.yml \
    up -d --force-recreate
