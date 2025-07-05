#include "headers.h"

extern int pTime;
extern char* pName;
extern int promptChange;
extern int bgNum;
extern pr arr[1000];

int main()
{
    init();
    while (1)
    {
        // Print appropriate prompt with username, systemname and directory before accepting input
        if(promptChange){
            prompt(pTime,pName);
        }
        else{
            prompt(0,NULL);
        }


        char input[4096];
        fgets(input, 4096, stdin);;
        inp(input);
        fflush(stdin);
    

    }
}
