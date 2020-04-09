#include "utils.h"

const char* parse_input(){
    char ch;
    char* input = malloc(sizeof(char) * BUFFER_SIZE_S);
    int i = 0;

    while ((read(STDIN_FILENO, &ch, 1)) && ch != '\n')
        input[i++] = ch;      

    return input;
}

bool arg_is_dir(char arg[]){
    return strchr(arg, '/') != NULL;
}

char* get_curr_dir(){
    size_t size = sizeof(char) * BUFFER_SIZE_L;
    char* cwd = malloc(size);

    if (getcwd(cwd, size) == NULL){
        perror("ERR getcwd");
        exit(1);
    }

    return cwd;
}

int traverse_dir(char* dir_name, struct dirinfo info[]){
    size_t i = 0;

    DIR* dir;
    struct dirent* ent;
    struct stat status;

    if (!(dir = opendir(dir_name))){
        perror(dir_name);
        exit(1);
    }        

    while((ent = readdir(dir)) != NULL){
        stat(ent->d_name, &status);
        
        if(strcmp(".", ent->d_name) == 0 || strcmp("..", ent->d_name) == 0)
            continue;
        else {
            struct dirinfo* cur_dir = &info[i++];
            snprintf(cur_dir->dir_name, sizeof(cur_dir->dir_name), "%s/%s", dir_name, ent->d_name);
            cur_dir->dir_ent = *ent;
            cur_dir->status = status;
        } 
    }

    closedir(dir);

    return 0;
}

bool is_symb_link(mode_t st_mode){
    return S_ISLNK(st_mode);
}

void duprintf(struct dirinfo info[], struct cmdfl cmd){

    char output[BUFFER_SIZE_L];    

    for (size_t j = 0; j < MAX_DIRS; j++){
        if (strcmp(info[j].dir_name, "") != 0){
            if (cmd.all) {
                if (cmd.bytes)
                    printf("%ld\t%ld\t%s\n", info[j].status.st_blocks/2, info[j].status.st_size, info[j].dir_name);
            }
            else {
                // if(S_ISDIR(ent->d_type & DT_DIR))
            }
        }
    }
}