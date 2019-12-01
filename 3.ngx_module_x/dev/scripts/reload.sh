#!/bin/bash 

cdir=`cd $(dirname $0); pwd`

ngxbin=$cdir/../src/nginx-1.16.1/objs/nginx

$ngxbin -s reload
