#pragma once 

#include <stdio.h>
#include <stdlib.h>

#include <string.h>
#include<dirent.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>


// CONSTANTS

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define BUFFER_SIZE_L 4096
#define BUFFER_SIZE_S 255

#define RD 0
#define WR 1


struct dirn {
    char* name_list[100];
}; 


// VARIOUS

const char* parseInput(){
    char ch;
    char* input = malloc(sizeof(char) * BUFFER_SIZE_S);
    int i = 0;

    while ((read(STDIN_FILENO, &ch, 1)) && ch != '\n')
        input[i++] = ch;      

    return input;
}

const char* substring(char aStr[], int start, size_t n){
    size_t size = n - (size_t)start;
    char* substr = malloc(size);
    size_t i;

    for (i = 0; i < size - 1; i++){
        substr[i] = aStr[start + i - 1];
    }

    substr[i] = '\0';

    return substr;
}

struct dirn traverseDir(char* dir_name){
    size_t i, j;

    DIR* dir;
    struct dirent* ent;
    struct stat status;
    struct dirn names;

    dir = opendir(dir_name);

    for (i = 0; i < ARRAY_SIZE(names.name_list); i++)
        memset(&names.name_list[i][0], 0, sizeof(*names.name_list[i])); 
    
    j = 0;
    while((ent = readdir(dir)) != NULL){
        stat(ent->d_name, &status);
        
        if(strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name))
            continue;
        else
            names.name_list[j++] = ent->d_name;
        
    }
    
    closedir(dir);

    return names;
}