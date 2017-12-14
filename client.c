#include "pipe_networking.h"

/* char ** parse_args( char * line, char * parse_for ) { */
/*     char** args = (char **)calloc(6, sizeof(char *)); */
/*     int i; */
/*     for(i = 0; line; i++) { */
/*         args[i] = strsep(&line, parse_for); */
/* 	args[i] = trim(args[i]); */
/*     } */
/*     args[i] = NULL; */
/*     return args; */
/* } */

int main(int argc, char *argv[]) {

  int to_server;
  int from_server;

  from_server = client_handshake( &to_server );

  printf("to_server: %d\n", to_server);
  printf("from_server: %d\n", from_server);
  
  char *input;
  
  while(1){

    
    printf("Input stuff:\n");
    fgets(input, 256, stdin);

    input[strlen(input) - 1] = 0;//removing the newline from the end of fgets 
    
    write(to_server, input, strlen(input) + 1);

    if(!strcmp(input, "exit")) {
      return 0;
    }
      
  }
}
