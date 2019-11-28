FROM nginx:1.16.1

WORKDIR /root
RUN apt-get update -y 
RUN apt-get install -y wget procps curl vim git net-tools 
RUN apt-get install -y zlib1g-dev libpcre3 libpcre3-dev
RUN apt-get install -y gcc g++ gdb automake autoconf libtool make
RUN apt-get install -y spawn-fcgi libfcgi-dev

# WORKDIR /root
# RUN wget 'http://nginx.org/download/nginx-1.16.1.tar.gz'
# RUN tar -xzvf nginx-1.16.1.tar.gz

WORKDIR /root
