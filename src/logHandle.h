#include "utils.h"

int create_log_file();

void initiate_time_count();

double instant_count();

void write_to_log(char action, char *info);

void close_log();

enum actions{
	CREATE,
	EXIT,
	RECV_SIGNAL,
	SEND_SIGNAL,
	RECV_PIPE,
	SEND_PIPE,
	ENTRY
};

char * choose_info(enum actions current_action);


