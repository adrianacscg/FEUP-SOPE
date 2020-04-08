#pragma once 

#include <stdio.h>
#include <stdlib.h>

#include "stdbool.h"
#include <string.h>
#include <dirent.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/times.h>


// CONSTANTS

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))

#define BUFFER_SIZE_L 4096
#define BUFFER_SIZE_S 255

#define RD 0
#define WR 1

#define MAX_DIRS 12


// STRUCTURES 

enum Commands {
    INVALID_COMMAND,
    HELP,
    ALL,
    BYTES,
    BLOCK_SIZE,
    COUNT_LINKS,
    DEREF,
    SEP_DIRS,
    MAX_DEPTH
};

struct cmdfl {
	bool all;
	bool bytes;
	bool block_size;
	bool count_links;		//count_links is always true
	bool deref;
	bool separate_dirs;
	bool max_depth;
};

struct dirinfo {
    char dir_name[BUFFER_SIZE_S];
    struct dirent dir_ent;
    struct stat status;
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

char* getCurrDir(){
    size_t size = sizeof(char) * BUFFER_SIZE_L;
    char* cwd = malloc(size);

    if (getcwd(cwd, size) == NULL){
        perror("ERR getcwd");
        exit(1);
    }

    return cwd;
}

int traverseDir(char* dir_name, struct dirinfo dir_info[]){
    size_t i = 0;

    DIR* dir;
    struct dirent* ent;
    struct stat status;

    if (!(dir = opendir(dir_name))){
        perror(dir_name);
        exit(1);
    }        

    strcat(dir_name, "/");

    while((ent = readdir(dir)) != NULL){
        stat(ent->d_name, &status);
        
        if(strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0)
            continue;
        else {
            // printf("%s%s\n", dir_name, ent->d_name);
    
            char child[] = "";
            
            strcat(child, dir_name);
            strcat(child, ent->d_name);
            
            strcpy(dir_info[i++].dir_name, child);      
            dir_info[i].dir_ent = *ent;
        } 
    }

    closedir(dir);

    return 0;
}