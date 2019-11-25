md5:
	rm -f md5
	gcc -std=c99 -g -o md5 -I /usr/local/opt/openssl/include/ -L /usr/local/opt/openssl/lib/ -lcrypto md5.c

clean: 
	rm -rf md5

test: 
	rm -f md5; make md5
	./md5.sh 20