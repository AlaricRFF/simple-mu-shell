//
// Created by Yuxiang Chen on 9/29/22.
//

#ifndef EECS201_ADV_UNIX_READ_PARSE_H
#define EECS201_ADV_UNIX_READ_PARSE_H
#define BUFSIZE 255
#define DELIM " \t\r\n\a"
#include <sys/wait.h>
#include <sys/types.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char* readLine(){
    char *line = malloc(sizeof(char) * BUFSIZE);
    int pos = 0;
    if (!line){
        fprintf(stderr,"allocation error\n");
        exit(EXIT_FAILURE);
    }
    while (1){
        int c = getchar();
        // TODO: EOF
        if (c == EOF){
            printf("\n");
            free(line);
            exit(0);
        }
        if (c == '\n'){
            line[pos] = '\0';
            return line;
        }
        else{
            line[pos] = (char)c;
        }
        pos ++;
    }
}

char **parse(char* line){

    int pos = 0;
    char** tokens = malloc(BUFSIZE * sizeof(char*));
    char* token;
    if (!tokens){
        fprintf(stderr,"allocation failure\n");
        exit(EXIT_FAILURE);
    }
    token = strtok(line,DELIM);
    while (token != NULL){
        tokens[pos] = token;
        pos ++;
        token = strtok(NULL, DELIM);
    }
    tokens[pos] = NULL;
    return tokens;
}

int execute(char **tokens){
    pid_t pid, wpid;
    int status;
    pid = fork();
    if (pid == 0){ // child process
        if(execvp(tokens[0],tokens) == -1){
            // failure
            return -1;
        }
        else if (pid < 0){
            fprintf(stderr,"error in forking.\nExiting ...\n");
            exit(-1);
        } else{
            do {
                waitpid(pid, &status, WUNTRACED);
            } while (!WIFEXITED(status) && !WIFSIGNALED(status));
        }
    }
    return 0;
}
#endif //EECS201_ADV_UNIX_READ_PARSE_H
