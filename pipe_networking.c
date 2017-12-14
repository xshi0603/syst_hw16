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

  c2s = open("WKP", O_RDONLY);

  char clientname[20];
  read(c2s, clientname, sizeof(clientname));

  remove("WKP");
  
  s2c = open(clientname, O_WRONLY);
  *to_client = open(clientname, O_WRONLY);
  
  write(s2c, "HELLO", strlen("HELLO") + 1);

  char response[20];
  read(c2s, response, sizeof(response));

  printf("to_server: %d\n", c2s);
  printf("from_server: %d\n", s2c);
  
  printf("---------------HANDSHAKE DONE-----------------\n");
  
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

  c2s = open("WKP", O_WRONLY);
  *to_server = open("WKP", O_WRONLY);

  write(c2s, filename, strlen(filename) + 1);
  
  int pipe = mkfifo(filename, 0644);

  s2c = open(filename, O_RDONLY);

  char buffer[20];

  read(s2c, buffer, sizeof(buffer));

  remove("privateFIFO");
  
  char* response = "removed FIFO";
  
  write(c2s, response, strlen(response) + 1);

  printf("to_client: %d\n", s2c);
  printf("from_client: %d\n", c2s);
  
  printf("---------------HANDSHAKE DONE-----------------\n");


  
  return s2c;
}
