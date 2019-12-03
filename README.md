# nginx-plugin

This project contains the personal recent works about nginx investigation on plugin, also openresty & lua related.

There are 3 folders, In 1.bin-test and 2.web-test folder, run `test_all.sh` to trigger the test. 

* 1.bin-test: run `test_all.sh` to compare language level performance by calculating 10000 numbers' md5 from 0 to 9999.
* 2.web-test: run `test_all.sh` to compare the same calculation triggered by web access while the web server is based on nginx or openresty.

  Till now, I compared 5 ways below: 
  
  a) nginx using `ngx_http_njs_module` to calculate 10000 times of md5 in njs.
  
  b) nginx using `proxy_pass` to the 3rd web application implemented with `nestjs`(a framework in nodejs) to calculate 10000 times of md5 in nodejs.
  
  c) openresty using `ngx_http_lua_module` to calculate 10000 times of md5 in luajit.
  
  d) nginx using `fastcgi_pass` to calculate 10000 times of md5 in fastcgi application. The application is started with 1 or 2 cgi app worker(s).
  
  e) nginx using a plugin(self developed) to calculate 10000 times of md5 in C.
  
* 3.nginx_module_x: 

  there are 2 sub folders: dev and use. 
  
  a) in dev folder, there are some code for nginx plugin development. 
  
  b) in use folder, there are some utilization sample on using kinds of nginx plugins.

**Note: **:

It will take some time to run it for the first time since all the running orchestrations are done in docker container, it may need some time to build or pull docker images. 
