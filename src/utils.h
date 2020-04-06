#pragma once 

#include <stdio.h>
#include <stdlib.h>

#include <string.h>

#include <fcntl.h>
#include <unistd.h>

#include <sys/wait.h>
#include <sys/types.h>


// CONSTANTS

#define ARRAY_SIZE(array) (sizeof(array) / sizeof(array[0]))
#define BUFFER_SIZE 4096

#define RD 0
#define WR 1


// VARIOUS

const char* parseInput(){
    char ch, input[BUFFER_SIZE];
    int i = 0;

    while ((read(STDIN_FILENO, &ch, 1)) && ch != '\n')
        input[i++] = ch;      

    return input;
}

const char* substring(char aStr[], int start, size_t n){
    size_t length = n - (size_t)start;
    char* substr = malloc(length);
    size_t i;

    for (i = 0; i < length-1; i++){
        substr[i] = aStr[start + i - 1];
    }

    substr[i] = '\0';

    return substr;
}
