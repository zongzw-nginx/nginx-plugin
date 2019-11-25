FROM openresty/openresty:latest

RUN apt-get update -y
RUN apt-get install -y gcc automake autoconf libtool make wget unzip curl

WORKDIR /root
RUN wget https://luarocks.org/releases/luarocks-3.2.0.tar.gz
RUN tar zxpf luarocks-3.2.0.tar.gz
WORKDIR /root/luarocks-3.2.0
RUN ./configure
RUN make
RUN make install

WORKDIR /root
RUN luarocks install md5 
RUN luarocks install luasocket

WORKDIR /root