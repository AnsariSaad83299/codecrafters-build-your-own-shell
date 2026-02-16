#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <unistd.h>
#include <sys/types.h>  
#include <sys/wait.h>

#define MAX_ARGS 64

int compare_strings(char *str1, char *str2){
    if(strcmp(str1, str2) == 0) return 1;
    else return 0;
}

int resolve_exe(char *name, char *file_path, size_t file_path_size){
    char *path = strdup(getenv("PATH"));
    char *dir = strtok(path, ":;");
    while(dir != NULL){
        snprintf(file_path, file_path_size, "%s/%s", dir, name);
        if(access(file_path, X_OK) == 0){
            free(path);
            return 1;
        }
        dir = strtok(NULL, ":;");
    }
    free(path);
    return 0;
}

int main(int argc, char *argv[]){
    setbuf(stdout, NULL);
    char command_line[1024];
    int cmd_argc;
    char *cmd_argv[MAX_ARGS];
    char file_path[4096];
    char current_working_directory[4096];

    while(true){
        printf("$ ");
        fgets(command_line, sizeof(command_line), stdin);
        command_line[strcspn(command_line, "\n")] = '\0';

        // cmd_argc = 0;
        // char *token = strtok(command_line, " ");
        // while(token != NULL && cmd_argc < (MAX_ARGS - 1)){
        //     cmd_argv[cmd_argc] = token;
        //     token = strtok(NULL, " ");
        //     cmd_argc++;
        // }

        char *start = command_line;
        char *end = command_line;
        bool in_single_quotes = false;
        while (*end != '\0') {
            if (*end == '\'') {
                in_single_quotes = !in_single_quotes;
                end++;
                continue;
            }

            if (*end == ' ' && !in_single_quotes) {
                *end = '\0';
                cmd_argv[cmd_argc++] = start;

                start = end + 1;
                while (*start == ' ') start++;

                end = start;
                continue;
            }

            end++;
        }
        if (start < end) {
            cmd_argv[cmd_argc++] = start;
        }
        cmd_argv[cmd_argc] = NULL; //execvp requires NULL terminated array

        for (int i = 0; i < cmd_argc; i++) {
            char *read = cmd_argv[i];
            char *write = cmd_argv[i];

            while (*read) {
                if (*read == '\'') {
                    read++;
                } else {
                    *write++ = *read++;
                }
            }
            *write = '\0';
        }

        if(cmd_argc == 0) continue; //empty input
        
        if(compare_strings(cmd_argv[0], "exit")) break;

        if(compare_strings(cmd_argv[0], "echo")){
            for(int i = 1; i < cmd_argc; i++){
                printf("%s ", cmd_argv[i]);
            }
            printf("\n");
            continue;
        }

        if(compare_strings(cmd_argv[0], "type")){
            if (compare_strings(cmd_argv[1], "echo") || compare_strings(cmd_argv[1], "exit") || compare_strings(cmd_argv[1], "type") || compare_strings(cmd_argv[1], "pwd") || compare_strings(cmd_argv[1], "cd")){
                printf("%s is a shell builtin\n", cmd_argv[1]);
            }
            else{
                if(resolve_exe(cmd_argv[1], file_path, sizeof(file_path))) printf("%s is %s\n", cmd_argv[1], file_path);

                else printf("%s: not found\n", cmd_argv[1]);
            }
            continue;
        }

        if(compare_strings(cmd_argv[0], "pwd")){
            getcwd(current_working_directory, sizeof(current_working_directory));
            printf("%s\n", current_working_directory);
            continue;
        }

        if(compare_strings(cmd_argv[0], "cd")){
            if(cmd_argv[1][0] == '~'){
                char *home_path = getenv("HOME");
                char full_path[strlen(home_path) + strlen(cmd_argv[1]) + 1];
                snprintf(full_path, sizeof(full_path), "%s%s", home_path, cmd_argv[1] + 1);
                chdir(full_path);
            }

            else if(chdir(cmd_argv[1]) != 0) printf("cd: %s: No such file or directory\n", cmd_argv[1]);

            continue;
        }
        
        if (resolve_exe(cmd_argv[0], file_path, sizeof(file_path))) {

            pid_t pid = fork();

            if (pid < 0) {
                perror("fork failed\n");
                continue;
            }

            if (pid == 0) {
              
                execv(file_path, cmd_argv);

                perror("execv failed\n");
                exit(1);
            }
            else {
                int status;
                waitpid(pid, &status, 0);
            }

        }
        else {
            printf("%s: command not found\n", cmd_argv[0]);
        }
    }
    
    return 0;
}