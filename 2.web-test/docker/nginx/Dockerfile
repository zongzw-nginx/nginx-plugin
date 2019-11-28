FROM nginx:1.16.1

WORKDIR /root
RUN apt-get update -y 
RUN apt-get install -y wget curl vim git procps net-tools 
RUN apt-get install -y zlib1g-dev libpcre3 libpcre3-dev
RUN apt-get install -y npm
RUN npm install -g forever
RUN apt-get install -y gcc g++ gdb automake autoconf libtool make
RUN apt-get install -y spawn-fcgi libfcgi-dev

WORKDIR /root
# RUN npm install -g @nestjs/cli
