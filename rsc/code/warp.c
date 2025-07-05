/*
 Need to include PATH DOES NOT EXIST ERROR
 ASSUMPTIONS:
        1. warp - as the first command after shell starting will not change the cwd.
*/

#include "../../headers.h"

extern char home[STRING_LENGTH];
extern char prev[STRING_LENGTH];

void warp(char* path, bool silent, bool updatePrev){
        char cwd[STRING_LENGTH];
        if(!path){
                if(updatePrev){
                        getcwd(cwd,STRING_LENGTH);
                        strcpy(prev,cwd);
                }

                path = home;
                int x  = chdir(path);
                if(x<0){
                        perror("ERROR");
                        printf("Cannot Change the Path\n");
                        return;
                }
        }
        else if (path[0] == '-'){
                path = prev;
                if(path){
                        int x = chdir(path);
                        if(x<0){
                                perror("ERROR");
                                printf("Cannot Change the Path\n");
                                return;
                        }
                }
        }
        else{
                if(updatePrev){
                        getcwd(cwd,STRING_LENGTH);
                        strcpy(prev,cwd);
                }

                char* tilde = strstr(path,"~");
                if(tilde == NULL){
                        int x  = chdir(path);
                        if(x<0){
                                perror("ERROR");
                                printf("Cannot Change the Path\n");
                                return;
                        }
                }
                else if(tilde[1] == '\0'){
                        int x = chdir(home);
                        if(x<0){
                                perror("ERROR");
                                printf("Cannot Change the Path\n");
                                return;
                        }
                }
                else if (tilde[1]=='/'){
                        int x = chdir(home);
                        x = chdir(tilde+2);

                        if(x<0){
                                perror("ERROR");
                                printf("Cannot Change the Path\n");
                                return;
                        }
                }
        }
        if(!silent){
                getcwd(cwd,STRING_LENGTH);
                printf("%s\n",cwd);
        }
}