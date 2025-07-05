#include "../../headers.h"

char home[STRING_LENGTH];
char prev[STRING_LENGTH];

int promptChange;
int bgNum = 0;



pr arr[1000];

void init(){
    getcwd(home,STRING_LENGTH);
    prev[0] = '\0';

    promptChange = 0;
}