#include "../../headers.h"


void inpExec(char* input);
void stage1Input(char* spCommand);
void stage2Input(char* spCommand);
void inpExec(char* input);

extern int bgNum;
extern pr arr[1000];

void inp(char* input){
     
        pid_t pid = waitpid(-1,NULL,WNOHANG);

        while(pid>0){
            // printf("%d\n",bgNum);
            printf("%d\n",pid);
            for(int i =0;i<bgNum;i++){
                if(arr[i].pid == pid){
                    printf("'%s' process with pid %d has exited normally.\n",arr[i].Name,pid);
                }
            }

            bgNum--;

            pid = waitpid(-1,NULL,WNOHANG);
        }
        

    input[strlen(input)-1] = '\0';
    char* pe = strstr(input,"pastevents");
    if(!pe){
        pastevents(input);
    }
    stage1Input(input);
}

void stage1Input(char* spCommand){
    char* comm;
    char tokenCpy[STRING_LENGTH];
    strcpy(tokenCpy,spCommand);
    
    char* fl = strstr(spCommand,";");
    if(!fl){
        stage2Input(tokenCpy);
    }
    else{
       
        char* token = strtok_r(tokenCpy,";\n",&comm);

        while(token){
            if(token[0]!='\0'){
                char tokenC[STRING_LENGTH];
                strcpy(tokenC,token);
                stage2Input(tokenC);
                // printf("%s\n",tokenC);
            }
            token = strtok_r(NULL,";\n",&comm);
        }
    }


}

void stage2Input(char* spCommand){
    char* comm1;
    char spCommandCpy[STRING_LENGTH];
    strcpy(spCommandCpy,spCommand);


    if(spCommandCpy[0] == '\0'){
        return;
    }
    char* a = strstr(spCommandCpy,"&");

    if(a){
        char* bgProc = strtok_r(spCommandCpy,"&\n",&comm1);
        char* fgProc = strtok_r(NULL,"&\n",&comm1);

        syscomm(bgProc,1);
        if(fgProc){
            syscomm(fgProc,0);
        }

         


    }

    else{
        inpExec(spCommandCpy);
    }

}

void inpExec(char* input){
    // printf("%s\n",input);

    char inputCpy[STRING_LENGTH];
    strcpy(inputCpy,input);

    char* delim = " \n";
    if(input[0]== '\0' || input == NULL){
        return;
    }
    char* token = strtok(input,delim);

    if(!strcmp(token,"pastevents")){
        token = strtok(NULL,delim);
        if(token){
            if(!strcmp(token,"execute")){
                token = strtok(NULL,delim);
                if(!token){
                    printf("ERROR: Invalid Index\n");
                    return;
                }
                int ind;
                int m = sscanf(token,"%d",&ind);
                printf("here");

                if(ind>15 || m<=0){
                    printf("ERROR: Invalid Index\n");
                    return;
                }
                stage1Input(pasteventsExecute(ind));
            }
            else if(!strcmp(token,"purge")){
                pasteventsPurge();
            }
        }
        else{
            pasteventsPrint();
        }
        
    
    
    }

    // Warp
    else if(!strcmp(token,"warp")){
        token = strtok(NULL,delim);
        bool f = 0;
        while(token!=NULL){
            f = 1;
            if(token)        
                warp(token,0,1);
            token = strtok(NULL,delim);
        }
        if(!f){
            warp(NULL,0,1);
        }
    }
    // Peek
    else if(!strcmp(token,"peek")){
        char* brkDown[3];

        int count = 0;
        while(token!=NULL){
            token = strtok(NULL,delim);
            if(token)
                brkDown[count++] = token;
        }
        if(count == 3){
            peek(brkDown[2],1,1);
        }
        else if (!strcmp(brkDown[0],"-la") || !strcmp(brkDown[0],"-al")){
            peek(brkDown[1],1,1);
        }
        else if(count == 1){
            peek(brkDown[0],0,0);
        }
        else if (brkDown[0][1] == 'l'){
            peek(brkDown[1],0,1);
        }
        else{
            peek(brkDown[1],1,0);
        }

    }

    else if (!strcmp(token,"proclore")){
        token = strtok(NULL," ");
        if(!token){
            proclore(getpid());
        }
        else{
            int pid = -1;
            int x = sscanf(token,"%d",&pid);
            if(x<=0){
                printf("ERROR: Invalid Process ID\n");
                return;
            }
            proclore(pid);
        }
    }

    else if (!strcmp(token,"seek")){
        bool dFlag = 0, fFlag = 0, eFlag = 0;
        
        char* fName;
        char* relPath;

        char* arg1 = strtok(NULL," \n");
        if(!strcmp(arg1,"-d")){
            dFlag = 1;
            arg1 = strtok(NULL," \n");

            if(!strcmp(arg1,"-e")){
                eFlag = 1;

                arg1 = strtok(NULL," \n");
                if(!arg1){
                    printf("ERROR: Not a Valid filename.\n");
                }

                fName = arg1;
                relPath = strtok(NULL," \n");

                seek(fName,relPath,dFlag,fFlag,eFlag);
                return;


            }
            else{
                fName = arg1;
                relPath = strtok(NULL," \n");

                seek(fName,relPath,dFlag,fFlag,eFlag);
                return;
            }
        }
        else if(!strcmp(arg1,"-f")){
            fFlag = 1;
            arg1 = strtok(NULL," \n");

            if(!strcmp(arg1,"-e")){
                eFlag = 1;

                arg1 = strtok(NULL," \n");
                if(!arg1){
                    printf("ERROR: Not a Valid filename.\n");
                }

                fName = arg1;
                relPath = strtok(NULL," \n");

                seek(fName,relPath,dFlag,fFlag,eFlag);
                return;

                
            }
            else{
                fName = arg1;
                relPath = strtok(NULL," \n");

                seek(fName,relPath,dFlag,fFlag,eFlag);
                return;
            }
        }
        else if(!strcmp(arg1,"-e")){
            eFlag = 1;
            arg1 = strtok(NULL," \n");

            if(!strcmp(arg1,"-d")){
                dFlag = 1;
                arg1 = strtok(NULL," \n");
                if(!arg1){
                    printf("ERROR: Not a Valid filename.\n");
                }

                fName = arg1;
                relPath = strtok(NULL," \n");

                seek(fName,relPath,dFlag,fFlag,eFlag);
                return;
            }
            else if(!strcmp(arg1,"-f")){
                fFlag = 1;
                arg1 = strtok(NULL," \n");
                if(!arg1){
                    printf("ERROR: Not a Valid filename.\n");
                }

                fName = arg1;
                relPath = strtok(NULL," \n");

                seek(fName,relPath,dFlag,fFlag,eFlag);
                return;
            }
            else{
                fName = arg1;
                relPath = strtok(NULL," \n");

                seek(fName,relPath,dFlag,fFlag,eFlag);
                return;
            }
        }
        else{
            fName = arg1;
            relPath = strtok(NULL," \n");

            seek(fName,relPath,dFlag,fFlag,eFlag);
            return;
        }


    }
    else{
        syscomm(inputCpy,0);
    }

}