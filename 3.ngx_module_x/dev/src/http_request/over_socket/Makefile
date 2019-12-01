all: clean soc test

soc:
	gcc http_request_over_socket.c -o soc

clean: 
	if [ -f soc ]; then \
		rm -rf soc; \
	fi

test:
	@echo 
	@echo "    ./soc <ip_address> <port> "
	@echo