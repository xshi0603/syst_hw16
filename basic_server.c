#include "pipe_networking.h"


int main() {

  int to_client;
  int from_client;

  from_client = server_handshake( &to_client );

  while(1){
    
    char clientInput[256];
    read(from_client, clientInput, sizeof(clientInput));

    //printf("recieved: %s\n", clientInput);
    
  }

}
