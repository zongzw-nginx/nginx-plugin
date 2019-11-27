#!/bin/bash 

cdir=`cd $(dirname $0); pwd`
docker run -v $cdir:/root/bin-test zongzw/gcc_lua_nodejs:latest \
    make -C /root/bin-test test