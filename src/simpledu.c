#include "instructions.h"
#include "stdbool.h"
#include "stdio.h"
#include "string.h"

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

struct commandFlags{

	bool all;
	bool bytes;
	bool block_size;
	bool count_links;		//count_links is always true
	bool deref;
	bool separate_dirs;
	bool max_depth;
};

void parseCommand(char* cmdArg, struct commandFlags *cmd_flags){

    if (strcmp(cmdArg, "-H")  == 0 || strcmp(cmdArg, "--help")  == 0){
        //cmd = HELP;
        char line_1[] = "List of commands:\n";
        char line_2[] = "\t• -a, --all – a informação exibida diz respeito também a ficheiros;\n";
        char line_3[] = "\t• -b, --bytes – apresenta o número real de bytes de dados (ficheiros) ou alocados (diretórios);\n";
        char line_4[] = "\t• -B, --block-size=SIZE – define o tamanho (bytes) do bloco para efeitos de representação;\n";
        char line_5[] = "\t• -l, --count-links – contabiliza múltiplas vezes o mesmo ficheiro;\n";
        char line_6[] = "\t• -L, --dereference – segue links simbólicos;\n";
        char line_7[] = "\t• -S, --separate-dirs – a informação exibida não inclui o tamanho dos subdiretórios;\n";
        char line_8[] = "\t• --max-depth=N – limita a informação exibida a N (0,1, …) níveis de profundidade de diretórios.\n";

        char help_msg[BUFFER_SIZE_L];
        char* lines[8] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8};                
        
        for (size_t i = 0; i < ARRAY_SIZE(lines); i++)
            strcat(help_msg, lines[i]);
            
        int len = strlen(help_msg);

        write(STDOUT_FILENO, help_msg, len);
        
    }
    else if (strcmp(cmdArg, "-a") == 0 || strcmp(cmdArg, "--all") == 0){
        //cmd = ALL;
        cmd_flags->all = true;
    }
    else if (strcmp(cmdArg, "-b") == 0 || strcmp(cmdArg, "--bytes") == 0){
        //cmd = BYTES;
        cmd_flags->bytes = true;
    }
    else if (strcmp(cmdArg, "-B") == 0 || strcmp(cmdArg, "--block-size") == 0){
        //cmd = BLOCK_SIZE;
        cmd_flags->block_size = true;
    }
    else if (strcmp(cmdArg, "-l") == 0 || strcmp(cmdArg, "--count-links") == 0){
        //cmd = COUNT_LINKS;
        cmd_flags->count_links = true;
    }
    else if (strcmp(cmdArg, "-L") == 0 || strcmp(cmdArg, "--dereference") == 0){
        //cmd = DEREF;
        cmd_flags->deref = true;
    }
    else if (strcmp(cmdArg, "-S") == 0 || strcmp(cmdArg, "--separate-dirs") == 0){
        //cmd = SEP_DIRS;
        cmd_flags->separate_dirs = true;
    }
    else if (strcmp(cmdArg, "--max-depth") == 0){
        //cmd = MAX_DEPTH;
        cmd_flags->max_depth = true;
    }
    else{
        //cmd = INVALID_COMMAND;
    	char error_msg[] = "Invalid command line argument.\nType --help or -H to get a list of possible input flags.\n";
        int len = strlen(error_msg);
        
        write(STDERR_FILENO, error_msg, len);
        
        exit(1);
    } 
}


int main(int argc, char* argv[]){

	struct commandFlags cmd_flags;
	cmd_flags.all = false;
	cmd_flags.bytes = false;
	cmd_flags.block_size = false;
	cmd_flags.count_links = true;		//count_links is always true
	cmd_flags.deref = false;
	cmd_flags.separate_dirs = false;
	cmd_flags.max_depth = false;


	const char *log_file_name = getenv("LOG_FILENAME");
	int fd1;
	fd1 = open(log_file_name, O_WRONLY | O_CREAT | O_EXCL, 0644);
	if (fd1 == -1) {
  		perror("Error on opening log file");
 	}

 	if(argc == 1){
 		//calling simpledu without giving any path or commands
		//we would want to handle this as calling simpledu with the path being the current directory and no more commands
 	}

	if(argc == 2){

		const char temp[] = "argv[1]";

		if(strchr(temp, '/') == NULL){
			//temp is a command
			parseCommand(argv[1], &cmd_flags);
		}
		else{
			//temp is a path
		}

	}
    
    if (argc > 2){

    	const char temp[] = "argv[1]";

		if(strchr(temp, '/') == NULL){
			//temp is a command
			for(int i = 1; i < argc; i++){
				parseCommand(argv[i], &cmd_flags);
			}
			
		}
		else{
			//temp is a path
			printf("Hi I'm here :D\n");
			for(int i = 2; i < argc; i++){
				parseCommand(argv[i], &cmd_flags);
			}
		}

    }

    return 0;
}
