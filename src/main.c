#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

int main(int argc, char *argv[]) {
  setbuf(stdout, NULL);
  char command[1024];

  while(true)
{  // Flush after every printf
  

  // TODO: Uncomment the code below to pass the first stage
  printf("$ ");
  fgets(command, sizeof(command), stdin);
  command[strcspn(command, "\n")] = '\0';
  printf("%s: command not found\n", command);}



  return 0;
}
