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

#define MAX_DIRS 100
#define MAX_CMDS 10


// GLOBALS

int blk_size;


// STRUCTURES 

enum actions{
	CREATE,
	EXIT,
	RECV_SIGNAL,
	SEND_SIGNAL,
	RECV_PIPE,
	SEND_PIPE,
	ENTRY
};


// VARIOUS

const char* parse_input();

const char* substring(char aStr[], int start, size_t n);

bool arg_is_dir(char arg[]);

char* get_curr_dir();

