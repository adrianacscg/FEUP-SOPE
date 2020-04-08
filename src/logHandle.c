#include "logHandle.h"


clock_t start, current;
struct tms t;
long ticks;

int log_filedes;

enum actions current_action;


void initiate_time_count(){
	start = times(&t);
    ticks = sysconf(_SC_CLK_TCK);
}

double instant_count(){
	current = times(&t);
    return (double)(current-start)/ticks;
}

int create_log_file(){
	current_action = CREATE;
	char *info = choose_info(current_action);

	const char* log_file_name = getenv("LOG_FILENAME");

	if (log_file_name == NULL) { 
		log_file_name = "logFile.txt"; 	//ficheiro a usar se LOG_FILENAME não estiver definida
	}
    

    if ((log_filedes = open(log_file_name, O_WRONLY | O_CREAT | O_TRUNC, 0644)) == -1) {
  		perror("Error on opening log file");
        exit(1);
 	}

 	write_to_log(current_action,info);

 	return log_filedes;
}

char * choose_info(enum actions current_action){
	char *info =" ";
	switch(current_action){
		case CREATE: {
			//os argumentos da linha de comandos
			break;
		}
		case EXIT: {
			//o código de saída (exit status)
			break;
		}
		case RECV_SIGNAL: {
			//o sinal recebido(por exemplo, SIGINT)
			break;
		}
		case SEND_SIGNAL: {
			//o sinal enviado seguido do pid do processo a quem se destina
			break;
		}
		case RECV_PIPE: {
			//a mensagem enviada
			break;
		}
		case SEND_PIPE: {
			//a mensagem recebida
			break;
		}
		case ENTRY: {
			//número de bytes(ou blocos) seguido do caminho
			break;
		}
		default: {

			break;
		}
	}
	return info;
}

void write_to_log(char action, char *info){

	double instant = instant_count();
	char instant_arr[8];
	pid_t pid = getpid();

	char log[BUFFER_SIZE_S];

	snprintf(instant_arr, 8, "%2.4f", instant);

	sprintf(log, instant_arr, pid, action, info);

	size_t nbytes = strlen(log);

    write(log_filedes, log, nbytes);
}


void close_log(){
	close(log_filedes);
}

	