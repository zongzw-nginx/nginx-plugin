#!/bin/bash

HOMEDIR=`cd $(dirname $0); pwd`/..
ab -n 2000 -c 1000 -w http://localhost/ > $HOMEDIR/logs/ab.out.html
