#include "pipe_networking.h"

/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  printf("---------------INITALIZING CONNECTION---------\n");
  int s2c, c2s;
  int pipe = mkfifo("WKP", 0644);

  //printf("opening WKP\n");
  
  c2s = open("WKP", O_RDONLY);

  //printf("opened WKP\n");
  
  char clientname[20];
  read(c2s, clientname, sizeof(clientname));

  //printf("recieve client name: %s\n", clientname);

  //printf("removing WKP\n");

  remove("WKP");
  
  //printf("removed WKP\n");
  
  //printf("opening clientFIFO\n");
 
  s2c = open(clientname, O_WRONLY);

  //printf("opened clientFIFO\n");

  //printf("writing HELLO to clientFIFO\n");
  
  write(s2c, "HELLO", strlen("HELLO") + 1);

  //printf("written\n");

  char response[20];
  read(c2s, response, sizeof(response));

  //printf("recieve response: %s\n", response);

  printf("---------------HANDSHAKE DONE-----------------\n");

  to_client = &s2c;
  
  return c2s;
}

/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  printf("---------------INITALIZING CONNECTION---------\n");
  int c2s, s2c;
  char *filename = "privateFIFO";

  //printf("opening WKP\n");

  c2s = open("WKP", O_WRONLY);

  //printf("opened WKP\n");
  
  //printf("sending file name to WKP\n");

  write(c2s, filename, strlen(filename) + 1);
  
  //printf("sent\n");

  //printf("making private pipe\n");
  
  int pipe = mkfifo(filename, 0644);

  //printf("made\n");
  
  //printf("opening private\n");
  
  s2c = open(filename, O_RDONLY);

  //printf("opened private\n");

  char buffer[20];

  //printf("reading response\n");
  
  read(s2c, buffer, sizeof(buffer));

  //printf("read\n");
  
  //printf("removing clientFIFO\n");

  remove("privateFIFO");
  
  //printf("removed\n");
  
  //printf("client recieved: %s\n", buffer);

  char* response = "removed FIFO";

  //printf("sending \"removed FIFO\"\n");
  
  write(c2s, response, strlen(response) + 1);

  //printf("sent");

  printf("---------------HANDSHAKE DONE-----------------\n");

  to_server = &c2s;
  
  return s2c;
}
