#ifndef mkdir_include
#define mkdir_include

#include <bits/stdc++.h>
#include <sys/stat.h>
#include <sys/types.h>

//copy contents of one char array into other up to an index
void copySubstring(char *a, char *b, int index){
    for(int i=0;i<index;i++)
        a[i] = b[i];
    a[index] = '\0';
}

void mkdir_r(char* path){
    int index = 0;
    char p = path[index]; //view 1 character at a time
    char partialPath[500]; //Char array to hold parital paths
    while(p != '\0'){
        p = path[index++];
        if( p == '/' || p == '\\' || p == '\0' ){
            copySubstring(partialPath,path,index);
            mkdir(partialPath,0777);
        }      
    }
    printf("Done\n");
}

#endif