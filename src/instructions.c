#include "instructions.h"

bool root = true;
int curr_depth, max_depth;
pid_t pid_main, pid_child = 0;

int parse_command(char* cmdArg, struct cmdfl* cmd_flags){

    if (strcmp(cmdArg, "-H")  == 0 || strcmp(cmdArg, "--help")  == 0){
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

        exit_log(1);
    }
    else if (strcmp(cmdArg, "-a") == 0 || strcmp(cmdArg, "--all") == 0)
        cmd_flags->all = true;
    else if (strcmp(cmdArg, "-b") == 0 || strcmp(cmdArg, "--bytes") == 0)
        cmd_flags->bytes = true;    
    else if (strcmp(cmdArg, "-B") == 0 || (strlen(cmdArg) >= 12 && strcmp(substring(cmdArg, 1, 12), "--block-size") == 0))
        cmd_flags->block_size = true;    
    else if (strcmp(cmdArg, "-l") == 0 || strcmp(cmdArg, "--count-links") == 0)
        cmd_flags->count_links = true;    
    else if (strcmp(cmdArg, "-L") == 0 || strcmp(cmdArg, "--dereference") == 0)
        cmd_flags->deref = true;    
    else if (strcmp(cmdArg, "-S") == 0 || strcmp(cmdArg, "--separate-dirs") == 0)
        cmd_flags->sep_dirs = true;    
    else if (strlen(cmdArg) >= 11 && strcmp(substring(cmdArg, 1, 11), "--max-depth") == 0){
        cmd_flags->max_depth = true;
        max_depth = atoi(substring(cmdArg, 13, strlen(cmdArg)));    
        curr_depth = max_depth;
    }
    else {
    	char error_msg[] = "Invalid command line argument.\nType --help or -H to get a list of possible input flags.\n";
        int len = strlen(error_msg);
        
        write(STDERR_FILENO, error_msg, len);
        
        exit_log(1);
    } 

    return EXIT_SUCCESS;
}


void init_flags(struct cmdfl* cmd_flags){
    cmd_flags->all = false;
	cmd_flags->bytes = false;
	cmd_flags->block_size = false;
	cmd_flags->count_links = true;		
	cmd_flags->deref = false;
	cmd_flags->sep_dirs = false;
	cmd_flags->max_depth = false;
}


int traverse_dir(char dir_name[], struct dirinfo info[], struct cmdfl cmd_flags){
    char path[BUFFER_SIZE_L];
    int dir_size = 0;
    size_t i = 0;

    DIR* dir;
    struct dirent* ent;
    struct stat status;

    if ((dir = opendir(dir_name)) == NULL){
        perror(dir_name);
        exit_log(DIR_ERROR);
    }        

    while((ent = readdir(dir)) != NULL){

        if(strcmp("..", ent->d_name) == EXIT_SUCCESS)  
            continue;   
        else if ((strcmp(".", ent->d_name) == EXIT_SUCCESS) && !root)
            continue;
        else {
            if (strcmp(".", ent->d_name) == 0 && root)
                root = false;

            snprintf(path, sizeof(path), "%s/%s", dir_name, ent->d_name);

            if (cmd_flags.deref) {
                if (stat(path, &status) == STAT_ERROR){
                    perror(path);
                    exit_log(STAT_ERROR);
                } 
            } else if (lstat(path, &status) == STAT_ERROR) {
                perror(path);
                exit_log(STAT_ERROR);
            }

            struct dirinfo* cur_dir = &info[i++];

            snprintf(cur_dir->dir_name, sizeof(cur_dir->dir_name), "%s", ent->d_name);
            snprintf(cur_dir->path, sizeof(cur_dir->path), "%s", path);
            cur_dir->dir_ent = *ent;
            cur_dir->status = status;  
    
            if (cmd_flags.bytes)
                cur_dir->size = status.st_size;
            else if (cmd_flags.block_size)
                cur_dir->size = (status.st_blocks*512)/blk_size;
            else 
                cur_dir->size = status.st_blocks/2;

            entry_log(dir_size, path);
        }
    }

    closedir(dir);

    return EXIT_SUCCESS;
}

int get_max_children(struct dirinfo info[]){
    int max_children = 0;
    for (size_t i = 0; i < MAX_DIRS; i++){
        if (strcmp(info[i].dir_name, "") != 0){
            if (S_ISDIR(info[i].status.st_mode))
                max_children += 1;
        }
    }

    return max_children;
}

void parent(int fd_in, pid_t pid, int* dir_size){
    int child_dir_size;

    if (getpgrp() == pid_main)
        pid_child = pid;

    read(fd_in, &child_dir_size, sizeof(child_dir_size));
    *dir_size += child_dir_size;

    char child_size_str[BUFFER_SIZE_S];
    sprintf(child_size_str, "%d", child_dir_size);
    recv_pipe_log(child_size_str);

    close(fd_in);
}

void child(int fd_out, pid_t pid, char path[], struct cmdfl cmd_flags, int dir_size){
    create_log();

    if (getpgrp() == pid_main)
        setpgid(pid, getpid());

    signal(SIGTERM, SIGTERM_handler);
    signal(SIGCONT, SIGCONT_handler);
    signal(SIGSTOP, SIGSTOP_handler);

    fetch_dir_info(path, cmd_flags);       
             
    write(fd_out, &dir_size, sizeof(dir_size));

    char dir_size_str[BUFFER_SIZE_S];
    sprintf(dir_size_str, "%d", dir_size);
    send_pipe_log(dir_size_str);

    close(fd_out);
}

int fetch_dir_info(char path[], struct cmdfl cmd_flags){   

    int fd[2], status, dir_size = 0, max_children;
    pid_t pid; 

    struct dirinfo dir_info[MAX_DIRS]; 

    traverse_dir(path, dir_info, cmd_flags);
    max_children = get_max_children(dir_info);

    // duprintf(dir_info, cmd_flags, dir_size);

    for (int i = 0; i <= max_children; i++){

        dir_size += dir_info[i].size;
        
        if (strcmp(dir_info[i].dir_name, ".") == EXIT_SUCCESS){
            if (cmd_flags.sep_dirs)
                printf("%d\t%s\n", dir_info[i].size, dir_info[i].path);
            else    
                printf("%d\t%s\n", dir_size, dir_info[i].path);
        }

        if (S_ISDIR(dir_info[i].status.st_mode) 
            && strcmp(dir_info[i].dir_name, ".") != EXIT_SUCCESS){
    
            if (cmd_flags.max_depth){
                if (curr_depth <= max_depth && curr_depth > 0)
                    curr_depth--; 
                else 
                    exit_log(EXIT_SUCCESS);
            }

            if (pipe(fd) < 0){
                perror("pipe error");
                exit_log(PIPE_ERROR);
            }

            switch ((pid = fork())){
                case -1:
                    perror("fork error");
                    exit_log(FORK_ERROR);
                case 0:
                    close(fd[RD]);
                    child(fd[WR], pid, dir_info[i].path, cmd_flags, dir_size);
                    break;
                default:
                    close(fd[WR]);
                    parent(fd[RD], pid, &dir_size);

                    if (cmd_flags.sep_dirs)
                        printf("%d\t%s\n", dir_info[i].size, dir_info[i].path);
                    else    
                        printf("%d\t%s\n", dir_size, dir_info[i].path);

                    // Terminate process
                    kill(pid, SIGTERM);
                    sleep(2);
                    if ((waitpid(pid, &status, WNOHANG)) >= 0)
                        kill(pid, SIGKILL);
                    
                    break;
            }
        } else if (S_ISLNK(dir_info[i].status.st_mode) || S_ISREG(dir_info[i].status.st_mode)){
            if (cmd_flags.all){
                if (cmd_flags.bytes)
                    printf("%ld\t%s\n", dir_info[i].status.st_size, dir_info[i].path);
                else if (cmd_flags.block_size)
                    printf("%ld\t%s\n", (dir_info[i].status.st_blocks*512)/blk_size, dir_info[i].path);
                else 
                    printf("%ld\t%s\n", dir_info[i].status.st_blocks/2, dir_info[i].path);
            }
        }
    }
     
    return dir_size;
}
