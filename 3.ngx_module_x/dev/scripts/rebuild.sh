#!/bin/bash 

cdir=`cd $(dirname $0); pwd`

srcdir=$cdir/../src
distdir=$cdir/../dist

(
    cd $srcdir/nginx-1.16.1
    modopts=""
    # for n in hello_world_module nginx-eval-module echo-nginx-module my_md5_module; do 
    for n in my_md5_module; do 
        modopts="$modopts --add-dynamic-module=$srcdir/$n"
        # modopts="$modopts --add-module=$srcdir/$n"
    done

        # --with-debug \
    ./configure \
        --with-compat \
        --prefix=$distdir \
        $modopts \
    && make && make install
)
