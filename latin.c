/*
  Command line interface for William Whitaker's Words, a popular Latin-English
  dictionary. Written by Eric Zheng in 2017. Feel free to modify/use this
  however you want. Just note that other people have probably written this
  before and written it better.
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#define MAX_MSG_LEN 1024
#define MAX_RES_LEN 4096 /* I assume that no translation will exceed this */

void error(char *msg) {
  fprintf(stderr, "%s\n", msg);
  exit(0);
}

int main(int argc, char *argv[]) {

  /* default to a Latin search -- only search English if [-E] given */
  int is_latin = 1;
  int opt;

  /* give a friendly warning if used incorrectly */
  while ((opt = getopt(argc, argv, "E")) != -1) {
    switch(opt) {
      case 'E': is_latin = 0; break;
      default: fprintf(stderr, "Usage: %s [-E] [word]\n", argv[0]); return 0;
    }
  }

  /* specify where/how we want to connect */
  int port_no = 80;
  char *host = "archives.nd.edu";
  struct hostent *server;
  struct sockaddr_in serv_addr;
  char message[MAX_MSG_LEN], response[MAX_RES_LEN];

  /* prepare HTTP GET requests */
  memset(message, 0, sizeof(message));
  if (is_latin)
    sprintf(message, "GET /cgi-bin/wordz.pl?keyword=%s HTTP/1.0\r\n\r\n", argv[1]);
   else
    sprintf(message, "GET /cgi-bin/wordz.pl?english=%s HTTP/1.0\r\n\r\n", argv[2]);

  /* open a socket */
  int sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd < 0) error("could not open socket");

  /* retrieve host info for Whitaker's Words */
  server = gethostbyname(host);
  if (server == NULL) error("could not find host for William Whitaker's Words");

  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(port_no);
  memcpy(&serv_addr.sin_addr.s_addr, server->h_addr, server->h_length);

  /* connect to Whitaker's Words */
  if (connect(sockfd, (const struct sockaddr *) &serv_addr,
              sizeof(serv_addr)) < 0)
    error("could not connect");

  /* send out request */
  if (send(sockfd, message, sizeof(message), 0) < 0)
    error("data transmission error");

  /* read back the response */
  if (recv(sockfd, response, sizeof(response), 0) < 0)
    error("data response error");

  /* extract the translation from the HTML reply */
  char *intro = strstr(response, "<pre>") + 5;
  char *end   = strstr(response, "</pre>");
  printf("%.*s\n", (int)(end - intro), intro);

  close(sockfd);
  return 0;
}
