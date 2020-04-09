#include "instructions.h"
#include "logHandle.h"


int main(int argc, char* argv[], char* envp[]){

	initiate_time_count();
	create_log_file(argc, argv);    
	
	struct cmdfl cmd_flags;
	init_flags(&cmd_flags);

    switch (argc) {
        case 1: {
            // calling simpledu without giving any path or commands
		    // we would want to handle this as calling simpledu with the path being the current directory and no more commands
            break;
        }
        case 2: {
            if (arg_is_dir(argv[1])){
                // arg is a path
            } else {
			    // arg is a command
			    parse_command(argv[1], &cmd_flags);
            }
            
            break;
        }
        default: {
            if (arg_is_dir(argv[1])){
                // arg is a path
                for(int i = 2; i < argc; i++)
                    parse_command(argv[i], &cmd_flags);


            } else {
                // arg is a command
                for(int i = 1; i < argc; i++)
                    parse_command(argv[i], &cmd_flags);
            }

            break;
        }
    }
    
    /*
    char __dirname[BUFFER_SIZE_S]; 
    strcpy(__dirname, get_curr_dir());
    printf("%s\n", __dirname);

    struct dirinfo info[MAX_DIRS]; 
    traverse_dir(__dirname, info);


    for(size_t j = 0; j < MAX_DIRS; j++){
        if (strcmp(info[j].dir_name, "") != 0)
            printf("%ld\t%ld\t%s\n", info[j].status.st_blocks/2, info[j].status.st_size, info[j].dir_name);
    }
    */    

    close_log();

    return 0;
}

