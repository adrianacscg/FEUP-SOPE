#include "instructions.h"
#include "logHandle.h"


int main(int argc, char* argv[]){

	initiate_time_count();
	create_log_file();
	
    const char *arg = argv[1];

	struct cmdfl cmd_flags;
	cmd_flags.all = false;
	cmd_flags.bytes = false;
	cmd_flags.block_size = false;
	cmd_flags.count_links = true;		
	cmd_flags.deref = false;
	cmd_flags.separate_dirs = false;
	cmd_flags.max_depth = false;

	

    switch (argc) {
        case 1: {
            // calling simpledu without giving any path or commands
		    // we would want to handle this as calling simpledu with the path being the current directory and no more commands
            break;
        }
        case 2: {
            if (strchr(arg, '/') == NULL){
			    // arg is a command
			    parseCommand(argv[1], &cmd_flags);
            } else {
                // arg is a path
            }
            break;
        }
        default: {
            if (strchr(arg, '/') == NULL){
                // arg is a command
                for(int i = 1; i < argc; i++)
                    parseCommand(argv[i], &cmd_flags);
            } else {
                // arg is a path
                for(int i = 2; i < argc; i++)
                    parseCommand(argv[i], &cmd_flags);
            }
            break;
        }
    }

    
    char __dirname[BUFFER_SIZE_S]; 
    strcpy(__dirname, getCurrDir());
    printf("%s\n", __dirname);

    struct dirinfo info[MAX_DIRS]; 
    traverseDir(__dirname, info);


    for(size_t j = 0; j < MAX_DIRS; j++){
        if (strcmp(info[j].dir_name, "") != 0)
            printf("%s\n", info[j].dir_name);
    }
    
    
    close_log();
    return 0;
}
