#include "pipe_networking.h"


int main(int argc, char *argv[]) {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  //printf("to_client: %d\n", to_client);
  //printf("from_client: %d\n", from_client);
  

  char clientInput[256];
  
  while(1){

    char returning[256] = "";
    
    read(from_client, clientInput, sizeof(clientInput));

    printf("Recieved: %s\n", clientInput);

    if(!strcmp(clientInput, "exit")) {
      return 0;
    }

    strcat(returning, clientInput);
    strcat(returning, " + SERVER WAS HERE");
    
    write(to_client, returning, sizeof(returning));
    
  }

}
