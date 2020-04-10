#pragma once
#include "utils.h"

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

int traverse_dir(char* dir_name, struct dirinfo info[]);

void duprintf(struct dirinfo info[], struct cmdfl cmd);

void fetch_dir_info(char dir_name[], struct cmdfl cmd_flags);