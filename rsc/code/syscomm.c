#include "../../headers.h"

extern int promptChange;
extern int bgNum;

extern pr arr[1000];

int pTime;
char* pName;

int syscomm(char* command, int bgFlag){

    char* args[100] = {NULL};
    char commandCpy[STRING_LENGTH];
    strcpy(commandCpy,command);

    char* tokenQ = strtok(commandCpy, "\"");
    tokenQ = strtok(NULL,"\"");

    int i = 0;
    int flag = 0;

    char* token = strtok(command," \n");
    while(token!=NULL){
        if(strstr(token,"\"")){
            flag=1;
        }

        if(!flag && token[0]!='\0'){
            args[i++] = token;
        }

        if(flag && strstr(token,"\"")){
            flag = 0;
        }
        token = strtok(NULL," \n");
    }
    if(tokenQ!=NULL){
        args[i++] = tokenQ;
    }

    int cPid = fork();

    if(cPid == 0){
        execvp(args[0],args);
        printf("ERROR: Invalid command\n");
    }
    else{
        if(bgFlag){
            arr[bgNum].pid = cPid;
            strcpy(arr[bgNum++].Name,args[0]);

            printf("[%d] %d\n",bgNum,cPid);
        }
        else{

            time_t start, end;
            time(&start);
            waitpid(cPid,NULL,0);
            time(&end);

            pTime = difftime(end,start);

            if(pTime>2){
                promptChange = 1;
                pName = args[0];
            }

        }
    }


}