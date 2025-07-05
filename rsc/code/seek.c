#include "../../headers.h"

int filtAll(const struct dirent* d){
    if(!strcmp(d->d_name,".") || !strcmp(d->d_name,"..")){
        return 0;
    }
    return 1;
};

int noSort(const struct dirent** d1 , const struct dirent** d2){
    return 1;
}

void seekR(char* fName, char* relPath,bool dFlag, bool fFlag, bool eFlag, char* ans, int* count,char* eFlagString);

void seek(char* fName, char* relPath,bool dFlag, bool fFlag, bool eFlag){

    char relPathcpy[STRING_LENGTH];
    if(relPath == NULL){
        char p[STRING_LENGTH];
        getcwd(p,STRING_LENGTH);
        relPath = p;
     }
     strcpy(relPathcpy,relPath);
    char* ans = (char*)malloc(sizeof(char)*STRING_LENGTH);
    ans[0] = '.';
    ans[1] = '\0';

    int count = 0;

    char eFlagString[STRING_LENGTH];

    seekR(fName,relPath,dFlag,fFlag,eFlag,ans,&count,eFlagString);


    if(eFlag && count == 1){

        struct stat s;
        stat(eFlagString,&s);

        if(S_ISREG(s.st_mode)){
            char Buffer[STRING_LENGTH] = {0};

            warp(relPathcpy,1,1);

            FILE* f = fopen(eFlagString,"r");

            int len = 0;
            int x;
            while(x = fread(Buffer,sizeof(char),STRING_LENGTH,f)){
                len+=x;
                printf("%s",Buffer);
            }

            warp("-",1,1);
        }

        else{
            warp(relPath,1,1);
            int st = chdir(eFlagString);
            if (st < 0){
                printf("Missing Permissions for this task\n");
                warp("-",1,1);
            }
        }

    }
}

void seekR(char* fName, char* relPath,bool dFlag, bool fFlag, bool eFlag, char* ans, int* count,char* eFlagString){
     

     int cPid = fork();
     if(cPid == 0){
        warp(relPath,1,1);

        int d;
        struct dirent** entryList;
        d = scandir(".",&entryList,filtAll,noSort);

        for(int i = 0 ;i<d;i++){
            if(entryList[i]->d_type == 4){
                char path[STRING_LENGTH] = "./\0";
                int ansLen = strlen(ans);
                strcat(ans,"/");
                strcat(ans,entryList[i]->d_name);

                if(!strcmp(entryList[i]->d_name,fName)&&!(fFlag && !dFlag)){
                    printf("\033[1;34m%s\n\033[1;0m",ans);
                    (*count)+=1;
                    strcpy(eFlagString,ans);
                }

                seekR(fName,strcat(path,entryList[i]->d_name),dFlag,fFlag,eFlag,ans,count,eFlagString);
                warp("..",1,1);
                ans[ansLen] = '\0';

            }
            else if (entryList[i]->d_type != 4 ){
                int ansLen = strlen(ans);
                char name[256];
                strcpy(name,entryList[i]->d_name);
                char* tok = strtok(name,".");

                if(!strcmp(tok,fName) && !(!fFlag && dFlag)){
                    strcat(ans,"/");
                    strcat(ans,entryList[i]->d_name);
                    printf("\033[1;32m%s\n\033[1;0m",ans);
                    
                    strcpy(eFlagString,ans);
                    (*count)+=1;

                    ans[ansLen] = '\0';
                }

            }
            
        }
        

     }
     else{
        wait(&cPid);
     }

}