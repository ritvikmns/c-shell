#include "../../headers.h"

char commands[15][STRING_LENGTH];
int rear = -1;
int fr = 0;
int dFlag = 0;
int maxCap = 0;

extern char home[STRING_LENGTH];
char string[STRING_LENGTH];

void readFile(){
    sprintf(string,"%s/hist.txt",home);
    FILE* f = fopen(string,"r");
    if(f==NULL){
        printf("ERROR: Cannot open/create the history file.\n");
    }

    fscanf(f,"%d",&rear);
    fscanf(f,"%d",&fr);
    fscanf(f,"%d",&dFlag);
    fscanf(f,"%d",&maxCap);
    fgetc(f);

    for(int i =0;i<maxCap;i++){
        fgets(commands[i],STRING_LENGTH,f);
        int len = strlen(commands[i]);
        commands[i][len-1] = '\0';

    }

    fclose(f);
}

void writeArray(){
    sprintf(string,"%s/hist.txt",home);
    FILE* f = fopen(string,"w");
    if(f==NULL){
        perror("History file not found\n");
    }


    fprintf(f,"%d\n",rear);
    fprintf(f,"%d\n",fr);
    fprintf(f,"%d\n",dFlag);
    fprintf(f,"%d\n",maxCap);
    
    for(int i =0;i<maxCap;i++){
        fprintf(f,"%s\n",commands[i]);
    }

    fclose(f);
}

void addInArray(char* command){

    strcpy(commands[(++rear)%15],command);

    if(rear == 15){
        dFlag = 1;
        rear = 0;
    }

    if(dFlag){
        fr++;
    }

    if(fr == 15){
        fr = 0;
    }

    if(maxCap < 15){
        maxCap++; 
    } 
}

void pastevents(char* command){
    readFile();

    if(!strcmp(commands[rear],command)){
        return;
    }
    if(command==NULL || command[0]=='\n'||command[0]=='\0'){
        return;
    }
    addInArray(command);
    writeArray();
}

void pasteventsPurge(){
    dFlag = 0;
    fr = 0;
    rear = -1;
    maxCap=0;
    writeArray();
}

char* pasteventsExecute(int index){
    char* command = (char*)malloc(sizeof(char)*STRING_LENGTH);
    
    readFile();
    
    if(index>maxCap){
        printf("ERROR: INVALID INDEX");
        return NULL;
    }

    int indArr = (rear-index+1)%15;
    strcpy(command,commands[indArr]);


    return command;
} 

void pasteventsPrint(){
    readFile();

    for(int i = fr ;i < fr+maxCap;i++){
        printf("%s\n",commands[i%15]);
    }
}




