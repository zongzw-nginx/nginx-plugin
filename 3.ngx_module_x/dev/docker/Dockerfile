FROM nginx:1.16.1

WORKDIR /root
RUN apt-get update -y
RUN apt-get install -y wget curl vim git tree unzip
RUN apt-get install -y procps zlib1g-dev libpcre3 libpcre3-dev
RUN apt-get install -y gcc gdb automake autoconf libtool make

#WORKDIR /root
#RUN wget 'http://nginx.org/download/nginx-1.16.1.tar.gz'
#RUN tar -xzvf nginx-1.16.1.tar.gz

WORKDIR /root
RUN echo 'while true; do sleep 1; done' > daemon.sh
