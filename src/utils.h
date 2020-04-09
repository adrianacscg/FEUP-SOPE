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

struct cmdfl {
	bool all;
	bool bytes;
	bool block_size;
	bool count_links;		//count_links is always true
	bool deref;
	bool sep_dirs;
	bool max_depth;
};

struct dirinfo {
    char dir_name[BUFFER_SIZE_L];
    struct dirent dir_ent;
    struct stat status;
}; 


// VARIOUS

const char* parse_input();

const char* substring(char aStr[], int start, size_t n);

bool arg_is_dir(char arg[]);

bool is_symb_link(mode_t st_mode);

char* get_curr_dir();

int traverse_dir(char* dir_name, struct dirinfo info[]);

void duprintf(struct dirinfo info[], struct cmdfl cmd);