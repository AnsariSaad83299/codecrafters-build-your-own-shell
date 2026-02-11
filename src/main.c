#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
  // Flush after every printf
  setbuf(stdout, NULL);

  // TODO: Uncomment the code below to pass the first stage
  printf("$ ");
  char command[100];
  fgets(command, sizeof(command), stdin);
  printf("%s", command);
  printf(": command not found");



  return 0;
}
