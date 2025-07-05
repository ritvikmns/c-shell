#include "../../headers.h"

char* stringReplace(char* str, char* subStr, int subLen);
extern char home[STRING_LENGTH];

void proclore(int pid){
    printf("pid : %d\n",pid);
    char state[3] = {'\0'};

    char path[100];
    sprintf(path,"/proc/%d/stat",pid);

    FILE* f = fopen(path,"r");
    char buffer[100];

    if(!f){
        printf("ERROR: Process does not exist now.\n");
        return;
    }
    else{
        int pgid;
        int fgid;

        fscanf(f,"%*d %*s %c",&state[0]);
        fscanf(f,"%*d %d %*d %*d %d",&pgid,&fgid);

        if(pgid == fgid){
            state[1] = '+';
        }

        printf("process status : %s\n",state);
        printf("Process Group : %d\n",pgid);

        sprintf(path,"/proc/%d/statm",pid);

        int mem;
        f = fopen(path,"r");
        fscanf(f,"%d",&mem);

        printf("Virtual Memory : %d\n",mem);

        char execPathRaw[STRING_LENGTH] = {'\0'};
        sprintf(path,"/proc/%d/exe",pid);

        int nBytes = readlink(path, execPathRaw, STRING_LENGTH);
        char* execPath = "Cannot read the executable path";


        if(nBytes>0){
            execPath = stringReplace(execPathRaw,home,strlen(home));
        }

        printf("Executable path : %s\n",execPath);

    }

}