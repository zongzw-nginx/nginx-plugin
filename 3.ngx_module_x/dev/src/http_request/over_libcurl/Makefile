all: clean httprequest test

httprequest:
	gcc http_request_over_libcurl.c -o httprequest -lcurl

clean: 
	if [ -f httprequest ]; then \
		rm -rf httprequest; \
	fi

test:
	@echo 
	@echo "    ./httprequest"
	@echo