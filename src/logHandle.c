#include "logHandle.h"

clock_t start, current;
struct tms t;
long ticks;

int log_filedes;
int arg_count;

char arg_values[INFO_MAX_SIZE];

char info[INFO_MAX_SIZE];
char current_action[ACTION_MAX_SIZE];


void initiate_time_count(){
	start = times(&t);
    ticks = sysconf(_SC_CLK_TCK);
}

double instant_count(){
	current = times(&t);
    return (double)(current-start)/ticks;
}

void create_log_file(int argc, char *argv[]){
	arg_count = argc;

	for (int i = 0; i < arg_count; i++)
	{
		strcat(arg_values, argv[i]);
	}

	const char* log_file_name = getenv("LOG_FILENAME");

	if (log_file_name == NULL) { 
		log_file_name = "logFile.txt"; 	//ficheiro a usar se LOG_FILENAME não estiver definida
	}

    if ((log_filedes = open(log_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
  		perror("Error on opening log file");
        exit(1);
 	}

 	create_log();
}



void write_to_log(char *current_action_str, char *info){

	double instant = instant_count();
	char instant_arr[8];
	char log[LOG_MAX_SIZE];

	pid_t pid = getpid();

	snprintf(instant_arr, 8, "%2.4f", instant);

	sprintf(log,"%s - %.8d - %s - %s\n" ,instant_arr, pid, current_action_str, info);

	size_t nbytes = strlen(log);
    write(log_filedes, log, nbytes);
}


void close_log(){
	exit_log(0);
	close(log_filedes);
}

void exit_log(int status){
	strcpy(current_action, "EXIT");
	sprintf(info, "%d", status);
	//strcpy(info, status);
	write_to_log(current_action, info);
}

void create_log(){
	strcpy(current_action, "CREATE");
	strcpy(info, arg_values);
	write_to_log(current_action, info);
}

void recv_sig_log(int signal){
	sprintf(info, "%d", signal);
	//strcpy(info, signal);
	strcpy(current_action, "RECV_SIGNAL");
	write_to_log(current_action, info);
}

void send_sig_log(pid_t pid, int signal){
	sprintf(info,"%d %d" ,pid, signal);
	strcpy(current_action, "SEND_SIGNAL");
	write_to_log(current_action, info);
}

void recv_pipe_log(char * message){
	strcpy(current_action, "RECV_PIPE");
	strcpy(info, message);
	write_to_log(current_action, info);
	
}

void send_pipe_log(char * message){
	strcpy(current_action, "SEND_PIPE");
	strcpy(info, message);
	write_to_log(current_action, info);
}

void entry_log(int byte_size, char * path){
	strcpy(current_action, "ENTRY");
	sprintf(info,"%d %s" ,byte_size, path);
}

	