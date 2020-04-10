#include "instructions.h"
#include "logHandle.h"
#include "sigHandle.h"
#include <signal.h>


int main(int argc, char* argv[], char* envp[]){

	initiate_time_count();
	create_log_file(argc, argv);    
	
    char __dirname[BUFFER_SIZE_S]; 
    strcpy(__dirname, get_curr_dir());
    
	struct cmdfl cmd_flags;
	init_flags(&cmd_flags);

    signal(SIGINT, SIGINT_handler);
    /*signal(SIGTERM,SIGTERM_handler);
    signal(SIGTSTP,SIGTSTP_handler);
    signal(SIGCONT,SIGCONT_handler);*/


    switch (argc) {
        case 1: {
            // fetch_dir_info(__dirname, cmd_flags);
            break;
        }
        case 2: {
            if (arg_is_dir(argv[1])){
                // argv[1] is a path
                // fetch_dir_info(argv[1], cmd_flags); 
            } else {
			    // argv[1] is a command
			    parse_command(argv[1], &cmd_flags);
                // fetch_dir_info(__dirname, cmd_flags); 
            }
            
            break;
        }
        default: {
            if (arg_is_dir(argv[1])){
                // argv[1] is a path
                for(int i = 2; i < argc; i++)
                    parse_command(argv[i], &cmd_flags);

                if (cmd_flags.block_size){
                    if (strlen(argv[2]) == 2)
                        blk_size = atoi(argv[3]);
                    else {
                        blk_size = atoi(substring(argv[2], 14, strlen(argv[2])));
                    }
                }

                // fetch_dir_info(argv[1], cmd_flags);
            } else {
                // argv[1] is a command
                for(int i = 1; i < argc - 1; i++)
                    parse_command(argv[i], &cmd_flags);

                if (cmd_flags.block_size){
                    if (strlen(argv[1]) == 2)
                        blk_size = atoi(argv[2]);
                    else {
                        blk_size = atoi(substring(argv[2], 14, strlen(argv[2])));
                    }
                }

                // fetch_dir_info(argv[argc-1], cmd_flags);
            }

            break;
        }
    }
    sleep(5);    
    exit_log(0);

    return 0;
}

