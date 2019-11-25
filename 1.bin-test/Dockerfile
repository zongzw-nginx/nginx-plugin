# build with:
#   docker build . -t zongzw/gcc_lua_nodejs:latest
FROM centos:7

RUN yum update -y
RUN yum install -y which wget unzip
RUN yum install -y gcc automake autoconf libtool make
RUN yum install -y openssl openssl-devel

RUN yum install -y epel-release
RUN yum install -y nodejs

WORKDIR /root
RUN yum install -y libtermcap-devel ncurses-devel libevent-devel readline-devel
RUN curl -R -O http://www.lua.org/ftp/lua-5.3.5.tar.gz
RUN tar zxf lua-5.3.5.tar.gz
WORKDIR /root/lua-5.3.5
RUN make linux test
RUN make install

WORKDIR /root
RUN wget https://luarocks.org/releases/luarocks-3.2.0.tar.gz
RUN tar zxpf luarocks-3.2.0.tar.gz
WORKDIR /root/luarocks-3.2.0
RUN ./configure
RUN make bootstrap
RUN make install

WORKDIR /root
RUN luarocks install md5 
RUN luarocks install luasocket

WORKDIR /root
