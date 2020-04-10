#include "utils.h"

#define INFO_MAX_SIZE 1024
#define ACTION_MAX_SIZE 20
#define LOG_MAX_SIZE 512

void create_log_file(int argc, char *argv[]);

void initiate_time_count();

double instant_count();

void write_to_log(char *current_action, char *info);

void choose_info(enum actions current_action);

void create_log();

void exit_log(int status);

void recv_sig_log(char * signal);

void send_sig_log(pid_t pid, char * signal);

void recv_pipe_log(char * message);

void send_pipe_log(char * message);

void entry_log(int byte_size, char * path);


