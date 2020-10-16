# CHILL
c micro framwork like flask

## Dependency
Chill used 

### GCC
chill used gcc attributes so it can't build on other compilers

### [FastCGI developer kit](https://github.com/FastCGI-Archives/fcgi2)
```sh
$ git clone https://github.com/FastCGI-Archives/fcgi2
$ cd fcgi2/
$ ./autogen.sh
$ ./configure
$ make
$ sudo make install
```

### [Lighttpd](https://redmine.lighttpd.net/projects/lighttpd/wiki/docs_modfastcgi)

make libhttpd config file
~~~
server.document-root = "/tmp/lighttpd-fastcgi-c" 

server.port = 8080

server.username = "www"
server.groupname = "www"

server.modules += ( "mod_fastcgi" )

mimetype.assign = (
  ".html" => "text/html",
  ".js" =>  "application/javascript",
  ".css" => "text/css",
  ".txt" => "text/plain",
  ".jpg" => "image/jpeg",
  ".png" => "image/png",
  ".svg" => "image/svg+xml",
  ".json" => "application/json",
)

static-file.exclude-extensions = ( ".fcgi", ".php", ".rb", "~", ".inc" )
index-file.names = ( "index.html" )

fastcgi.debug = 1
fastcgi.server = (
  "/" => ((
    "bin-path" => "chill_fcgi.fcgi",
    "socket" => "/tmp/chill_fastcgi.sock",
    "check-local" => "disable",
    "max-procs" => 2,
  ))
)
~~~

## Useage

The way to build chill application

~~~sh
$ gcc chill_fcgi.c -o chill_fcgi.fcgi -lfcgi -O2  -Wall -Wextra -pedantic -std=c11
~~~

After building the fcgi chill application 

~~~sh
lighttpd -D -f lighttpd.conf
http://127.0.0.1:8080/main?a=kk
~~~
