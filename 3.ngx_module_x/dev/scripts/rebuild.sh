#!/bin/bash 

cdir=`cd $(dirname $0); pwd`

srcdir=$cdir/../src
distdir=$cdir/../dist

(
    cd $srcdir/nginx-1.16.1
    ./configure \
        --with-debug \
        --prefix=$distdir \
        --add-dynamic-module=$srcdir/nginx-eval-module \
        --add-dynamic-module=$srcdir/echo-nginx-module \
    && make && make install
)
