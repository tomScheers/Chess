#include "network/network.h"

#include <curl/curl.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define PORT 50000

int main() {
  int action;
  while (action != 1 && action != 2) {
    printf("What action would you like to perform?:\n1. Create server\n2. Join "
           "server\n");
    scanf("%d", &action);
  }
  switch (action) {
  case 1: {
    char *IPCode = NET_getIPAddress();
    printf("IP Code: %s\n", IPCode);
    int server = NET_makeServerSocket(PORT);
    NET_writeSocket(server, "HELLO WORLD");
    char *msg = NET_readSocket(server);
    while (msg == NULL) {
      msg = NET_readSocket(server);
      sleep(1);
    };
    printf("Message from client: %s\n", msg);
    NET_closeSocket(server);
    break;
  }
  case 2: {
    char *IPCode = malloc(sizeof(char *) * 256);
    printf("Please provide the game IP code: ");
    scanf("%s", IPCode);
    printf("IP: %s\n", IPCode);
    int server = NET_makeClientSocket(IPCode, PORT);
    char *msg = NET_readSocket(server);
    printf("MSG: %s\n", msg);
    printf("Wait 5 seconds\n");
    sleep(5);
    NET_writeSocket(server, "IS THIS THERE???");
    NET_closeSocket(server);
    break;
  }
  }
}
