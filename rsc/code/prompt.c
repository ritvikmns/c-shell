#include "../../headers.h"

extern char home[STRING_LENGTH];
extern int promptChange;

extern int bgNum;
extern pr arr[1000];

char* stringReplace(char* str, char* subStr, int subLen){
    char* strN = strstr(str,subStr);
    
    if(strN==NULL){
        return str;
    }

    str+=subLen-1;
    str[0] = '~';
    return str;
}


void prompt(int pTime, char* pName) {

   
    
    char* uName = getlogin();

    char sysName[STRING_LENGTH];
    char path[STRING_LENGTH];

    gethostname(sysName,STRING_LENGTH);
    getcwd(path,STRING_LENGTH);

    char* pathN = stringReplace(path,home,strlen(home));

    if(promptChange){
        printf("<%s@%s:%s %s : %ds>",uName,sysName,pathN,pName,pTime); 

    }
    else{
        printf("<%s@%s:%s>",uName,sysName,pathN); 
    }
}


