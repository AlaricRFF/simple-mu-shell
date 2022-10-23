#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>
#include "read_parse.h"



int main(int argc, char *argv[]){
    char usr[BUFSIZE];
    char *usrVar = "USER";
    char *homeVar = "HOME";
    char cwd[BUFSIZE];

    // TODO: read USER name
    // Make sure envar actually exists
    if(!getenv(usrVar)){
        fprintf(stderr, "The environment variable %s was not found.\n", usrVar);
        exit(1);
    }
    // Make sure the buffer is large enough to hold the environment variable
    // value.
//    int t = snprintf(usr, BUFSIZE, "%s", getenv(usrVar));
//    if(t >= BUFSIZE){
//        fprintf(stderr, "BUFSIZE of %d was too small. Aborting\n", BUFSIZE);
//        exit(1);
//    }
    strcpy(usr, getenv(usrVar));
    while (1){
        // TODO: read current directory
        // check if error in reading cwd
        if (getcwd(cwd,sizeof(cwd)) == NULL) {
            perror("getcwd() error");
            exit(1);
        }
        // TODO: prompt user
        printf("%s:%s$ ",usr,cwd);
        char* line = readLine();
        // TODO: parse input
        char** tokens = parse(line);
        // TODO: empty input
        if (!tokens[0] ){
            continue;
        }
        // TODO: exit int
        if (strcmp(tokens[0],"exit") == 0){
            if (tokens[1]){
                exit(atoi(tokens[1]));
            }
            else
                exit(0);
        }
        // TODO: cd
        if (strcmp(tokens[0],"cd") == 0){
            if (chdir(tokens[1]) != 0){
                fprintf(stderr,"mush: cd: no such file or directory '%s'\n",tokens[1]);
            }

        }
        else{
            if (execute(tokens) == -1){
                fprintf(stderr,"mush: command '%s' not found",tokens[0]);
            }
        }
        free(line);
        free(tokens);
    }

    // forever loop
        // print prompt
        // receive user input
        // handle EOF
        // tokenize input
        // handle `exit` and `cd`
        // fork
        // child
            // execute commnad
            // handle errors
        // parent
            // wait for child
}


