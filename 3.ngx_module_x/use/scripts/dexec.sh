#!/bin/bash 

docker exec \
    --env COLUMNS=`tput cols` \
    --env LINES=`tput lines` \
    -it USENGX bash