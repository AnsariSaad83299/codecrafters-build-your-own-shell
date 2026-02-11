#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  char command_line[1024];
  char args[1024];

  while(true)
  {  
    printf("$ ");
    fgets(command_line, sizeof(command_line), stdin);
    command_line[strcspn(command_line, "\n")] = '\0';
    size_t idx = strcspn(command_line, " ");
    command_line[idx] = '\0';
    args[0] = command_line[idx + 1];


    if(strcmp(command_line, "exit") == 0){
      break;
    }
    else if(strcmp(command_line, "echo") == 0){
      printf("%s\n", args);
    }
    else{
      printf("%s: command not found\n", command_line);
    }
  }



  return 0;
}
