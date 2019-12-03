# nginx-plugin

This project contains the personal recent works about nginx investigation on plugin, also openresty & lua related.

There are 3 folders here:

* 1.bin-test: run `test_all.sh` to compare language level performance by calculating 10000 numbers' md5 from 0 to 9999.
* 2.web-test: run `test_all.sh` to compare the same calculation triggered by web access while the web server is based on nginx or openresty.
* 3.nginx_module_x: 

  there are 2 sub folders: dev and use. 
  
  a) in dev folder, there are some code for nginx plugin development. 
  
  b) in use folder, there are some utilization sample on using kinds of nginx plugins.
