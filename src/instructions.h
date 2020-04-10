#pragma once

#include "utils.h"

#define STAT_ERROR -1
#define DIR_ERROR 2
#define PIPE_ERROR 3
#define FORK_ERROR 4


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


int parse_command(char* cmdArg, struct cmdfl* cmd_flags);

void init_flags();

int traverse_dir(char dir_name[], struct dirinfo info[], struct cmdfl cmd_flags);

void duprintf(struct dirinfo info[], struct cmdfl cmd);

void parent(int fd_in, pid_t pid, int* dir_size);

void child(int fd_out, char dir_name[], struct cmdfl cmd_flags);

int fetch_dir_info(char dir_name[], struct cmdfl cmd_flags);