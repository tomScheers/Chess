#include "network.h"

#include <arpa/inet.h>
#include <curl/curl.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>

#define MAX 5
#define SA struct sockaddr


void NET_writeSocket(int socket, char* move) {
  printf("Message: %s\n", move);
  write(socket, move, strlen(move));
}

char* NET_readSocket(int socket) {
  char* msg = malloc(sizeof(char) * MAX);
  int bytesRead = read(socket, msg, MAX - 1);
  msg[bytesRead] = '\0';
  return msg;
}

void NET_closeSocket(int socket) {
  close(socket);
}

int NET_makeServerSocket(int port) {
  int sockfd, connfd;
  socklen_t len;
  struct sockaddr_in servaddr, cli;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  } else
    printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign IP, port
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = htonl(INADDR_ANY);
  servaddr.sin_port = htons(port);

  // Binding newly created socket to given IP and verification
  if ((bind(sockfd, (SA *)&servaddr, sizeof(servaddr))) != 0) {
    printf("socket bind failed...\n");
    exit(0);
  } else
    printf("Socket successfully binded..\n");

  // Now server is ready to listen and verification
  if ((listen(sockfd, 5)) != 0) {
    printf("Listen failed...\n");
    exit(0);
  } else
    printf("Server listening..\n");
  len = sizeof(cli);

  // Accept the data packet from client and verification
  connfd = accept(sockfd, (SA *)&cli, &len);
  if (connfd < 0) {
    printf("server accept failed...\n");
    exit(0);
  } else
    printf("server accept the client...\n");

  return connfd;
}


int NET_makeClientSocket(char *ip, int port) {
  printf("IP in make client func: %s\n", ip);
  int sockfd;
  struct sockaddr_in servaddr;

  // socket create and verification
  sockfd = socket(AF_INET, SOCK_STREAM, 0);
  if (sockfd == -1) {
    printf("socket creation failed...\n");
    exit(0);
  } else
    printf("Socket successfully created..\n");
  bzero(&servaddr, sizeof(servaddr));

  // assign ip, port
  servaddr.sin_family = AF_INET;
  servaddr.sin_addr.s_addr = inet_addr(ip);
  servaddr.sin_port = htons(port);

  // connect the client socket to server socket
  if (connect(sockfd, (SA *)&servaddr, sizeof(servaddr)) != 0) {
    printf("connection with the server failed...\n");
    exit(0);
  } else
    printf("connected to the server..\n");
  return sockfd;
}

static size_t writeCallBack(void *ptr, size_t size, size_t nmemb, char *data) {
  size_t totalSize = size * nmemb;
  strncat(data, (char *)ptr, totalSize);
  return totalSize;
}

char *NET_getIPAddress() {
  CURL *curl;
  CURLcode res;
  static char ip[64] = {0};

  // Initialize libcurl
  curl = curl_easy_init();
  if (!curl) {
    fprintf(stderr, "Failed to initialize libcurl.\n");
    return ip;
  }

  curl_easy_setopt(curl, CURLOPT_URL, "https://api64.ipify.org");
  curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeCallBack);
  curl_easy_setopt(curl, CURLOPT_WRITEDATA, ip);

  res = curl_easy_perform(curl);
  if (res != CURLE_OK) {
    fprintf(stderr, "curl_easy_perform() failed: %s\n",
            curl_easy_strerror(res));
  }

  curl_easy_cleanup(curl);
  return ip;
}
