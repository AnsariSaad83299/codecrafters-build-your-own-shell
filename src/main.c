#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  char command_line[1024];  

  while(true)
  {  
    printf("$ ");
    fgets(command_line, sizeof(command_line), stdin);
    command_line[strcspn(command_line, "\n")] = '\0';

    char *command = strtok(command_line, " ");
    char *args = strtok(NULL, " ");
    

    if(strcmp(command, "exit") == 0){
      break;
    }
    else if((strcmp(command, "echo") == 0) && (args != NULL)){

      while(args != NULL){
        printf("%s ", args);
        args = strtok(NULL, " ");
      }
      printf("\n");
    }
    else if(strcmp(command, "type") == 0){
      if (strcmp(args, "echo") == 0 || strcmp(args, "exit") == 0 || strcmp(args, "type") == 0){
        printf("%s is a shell builtin\n", args);
      }
      else{
    
        char *dir = strtok(getenv("PATH"), ";:");
        while(dir != NULL){
          char file_path[strlen(dir) + 1 + strlen(args) + 1];
          snprintf(file_path, sizeof(file_path), "%s/%s", dir, args);
          if(access(file_path, X_OK)){
            printf("%s is %s\n", args, file_path);
            continue;
          }

        }
        
        printf("%s: not found\n", args);
      }
    }
    else{
      printf("%s: command not found\n", command);
    }
  }



  return 0;
}
