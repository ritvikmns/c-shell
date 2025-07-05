/*
    Same error handling is required as of warp. (i.e. directory does not exist)
    Need to write printDetailed
    Assumptions: hitting peek - as the first command shows peek ~
*/

#include "../../headers.h"

extern char home[STRING_LENGTH];
char prevPeek[STRING_LENGTH];
char* perm = "drwxrwxrwx";

void lower(const char* src, char* dest, int lenSrc){
    for(int i =0;i<lenSrc;i++){
        if(src[i]>='A' && src[i] <= 'Z'){
            dest[i] = src[i]+'a'-'A';
        }
        else{
            dest[i] = src[i];
        }
    }
    dest[lenSrc] = '\0';
}

void binary(bool arr[10], unsigned int mode){
    int i = 9;
    while(i>=0){
        int rem = mode%2;
        mode/=2;
        arr[i--] = rem;
    }
}


int filter(const struct dirent* d){
    if(d->d_name[0]!='.'){
        return 1;
    }
    return 0;
}

int filterAll(const struct dirent* d){
    return 1;
}


int cmp(const struct dirent** d1 , const struct dirent** d2){
    int len1 = strlen((*d1)->d_name);
    int len2 = strlen((*d2)->d_name);

    char buffer1[len1+1];
    char buffer2[len2+1];

    lower((*d1)->d_name,buffer1,len1);
    lower((*d2)->d_name,buffer2,len2);

    return (strcmp(buffer1,buffer2));
}


void printNormal(struct dirent** entryList, int d){
    int c = 0;

    while (c!=d) {
        if(entryList[c]->d_type == 4){
            printf("\033[1;34m%s\n\033[1;0m", entryList[c]->d_name);
        }
        else{
                struct stat s;
                bool bin[10];
                stat(entryList[c]->d_name,&s);

                unsigned int mode = s.st_mode;
                binary(bin,mode);

                if(bin[3] || bin[5] || bin[9]){
                    printf("\033[1;32m%s\n\033[1;0m", entryList[c]->d_name);
                }

                else{
                    printf("%s\n", entryList[c]->d_name);
                }
        }
        c++;

    }
}

void printPerm(bool bin[10]){
    for(int i =0;i<10;i++){
        if(bin[i]){
            printf("%c",perm[i]);
        }
        else{
            printf("-");
        }
    }
    printf(" ");
}

void printTime(long epoch){
    struct tm t;
    char buf[15];
    t = *localtime(&epoch);
    strftime(buf,15,"%b %d %H:%M",&t);
    printf("%s ",buf);

}


void printDetailed(struct dirent** entryList, int d){
    int c = 0;

    long size = 0;

    struct stat s;
    
    for(int i = 0;i<d;i++){
        stat(entryList[i]->d_name,&s);
        size += s.st_blksize;
    }

    printf("total: %lld\n",size/512);

    while (c!=d) {
        stat(entryList[c]->d_name,&s);
        unsigned int mode = s.st_mode;

        bool bin[10];
        binary(bin,mode);

        char ans[STRING_LENGTH]; 

        
        if(entryList[c]->d_type == 4){
            stat(entryList[c]->d_name,&s);

            struct passwd *pw = getpwuid(s.st_uid);
            struct group  *gr = getgrgid(s.st_gid);



            bin[0] = 1;
            printPerm(bin);
            printf("%d ",s.st_nlink);

            printf("%s ",pw->pw_name);
            printf("%s ",gr->gr_name);

            printf("%d ", s.st_size);
            printTime(s.st_ctime);

            printf("\033[1;34m%s\n\033[1;0m", entryList[c]->d_name);
        }
        else{ 

                stat(entryList[c]->d_name,&s);

                struct passwd *pw = getpwuid(s.st_uid);
                struct group  *gr = getgrgid(s.st_gid);

                printPerm(bin);
                printf("%d ",s.st_nlink);

                printf("%s ",pw->pw_name);
                printf("%s ",gr->gr_name);

                printf("%lld ", s.st_size);
                printTime(s.st_ctime);
                


                if(bin[3] || bin[5] || bin[9]){
                    printf("\033[1;32m%s\n\033[1;0m", entryList[c]->d_name);
                }

                else{
                    printf("%s\n", entryList[c]->d_name);
                }
        }
        c++;

    }
}


void peek(char* path,bool aFlag, bool lFlag){
    if(path==NULL || path[0] == '\0'){
        printf("ERROR: PATH IS EMPTY\n");
        return;
    }
    else{
        if(path[0] == '-'){
            peek(prevPeek,aFlag,lFlag);
        }
        else{
            int pid = fork();
            if(pid == 0){

                warp(path,1,1);

                int d;
                struct dirent** entryList;

                if(aFlag && lFlag){
                    d = scandir(".",&entryList,filterAll,cmp);
                    printDetailed(entryList,d);
                }
                else if(lFlag){
                    d = scandir(".",&entryList,filter,cmp);
                    printDetailed(entryList,d);
                }
                else if (aFlag){
                    d = scandir(".",&entryList,filterAll,cmp);
                    printNormal(entryList,d);
                }
                else{
                    d = scandir(".",&entryList,filter,cmp);
                    printNormal(entryList,d);
                }

                warp("-",1,1);
                exit(0);
            }
            else{
                strcpy(prevPeek,path);
                wait(&pid);
            }
        
    }

    }
}