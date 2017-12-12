#include "pipe_networking.h"


/*=========================
  server_handshake
  args: int * to_client

  Perofrms the client side pipe 3 way handshake.
  Sets *to_client to the file descriptor to the downstream pipe.

  returns the file descriptor for the upstream pipe.
  =========================*/
int server_handshake(int *to_client) {
  int s2c, c2s;
  int pipe = mkfifo("WKP", 0644);
  
  c2s = open("WKP", O_RDONLY);

  struct stat st;
  stat("WKP", &st);

  char *clientname = calloc(st.st_size, sizeof(char));
  read(c2s, clientname, st.st_size);
  
  s2c = open(clientname, O_WRONLY);
  write(s2c, "HELLO", strlen("HELLO") + 1);
  
  return 0;
}

/*=========================
  client_handshake
  args: int * to_server

  Perofrms the client side pipe 3 way handshake.
  Sets *to_server to the file descriptor for the upstream pipe.

  returns the file descriptor for the downstream pipe.
  =========================*/
int client_handshake(int *to_server) {
  int c2s, s2c;
  char *filename = "privateFIFO";
  int pipe = mkfifo(filename, 0644);
  
  s2c = open(filename, O_RDONLY);
  c2s = open("WKP", O_WRONLY);

  write(c2s, filename, strlen(filename) + 1);

  char *buffer;
  read(s2c, buffer, 6);
  
  printf("client recieved: %s\n", buffer);
  
  return 0;
}
