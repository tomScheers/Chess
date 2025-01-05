#ifndef NET_H
#define NET_H

int NET_makeClientSocket(char* ip, int port);
int NET_makeServerSocket(int port);
char* NET_getIPAddress();
void NET_writeSocket(int socket, char* msg);
char* NET_readSocket(int socket);
void NET_closeSocket(int socket);

#endif
