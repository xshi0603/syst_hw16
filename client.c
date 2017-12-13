#include "pipe_networking.h"


int main() {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  /*
  while(1){


    char *input = malloc(256);
  
    printf("Input stuff:\n");
    fgets(input, 256, stdin);

    printf("writing\n");
    
    write(c2s, input, strlen(input) + 1);

    printf("written\n");
      
  }
  free(input);
  */
}
