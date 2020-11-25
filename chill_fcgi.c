#include <fcgi_stdio.h>
#include <stdlib.h>

int main(void) {
  while (FCGI_Accept() >= 0) {
    printf("Status: 200 OK\r\n");
    printf("Set-Cookie: a=aaa;\r\n");
    printf("Content-type: text/html\r\n\r\n");
    char* cookie = getenv("HTTP_COOKIE");
    if (cookie == NULL) {
      cookie = "NULL";
    }

    printf(
        "<!doctype>"
        "<html>"
        "<body>"
        "from fastcgi with lighttpd! <br>"
        "set cookie %s<br>"
        "%s<br>"
        "</body>"
        "</html>\n",
        cookie, getenv("QUERY_STRING"));
  }
  return EXIT_SUCCESS;
}