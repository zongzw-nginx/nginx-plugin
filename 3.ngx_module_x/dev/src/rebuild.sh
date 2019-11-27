#!/bin/bash 

cdir=`cd $(dirname $0); pwd`

(
    cd $cdir/nginx-1.16.1
    ./configure \
        --with-debug \
        --prefix=/etc/nginx \
        --add-dynamic-module=$cdir/nginx-eval-module \
        --add-dynamic-module=$cdir/echo-nginx-module \

    make
)
