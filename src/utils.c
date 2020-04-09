#include "utils.h"

const char* parse_input(){
    char ch;
    char* input = malloc(sizeof(char) * BUFFER_SIZE_S);
    int i = 0;

    while ((read(STDIN_FILENO, &ch, 1)) && ch != '\n')
        input[i++] = ch;      

    return input;
}

const char* substring(char aStr[], int start, size_t n){
    size_t size = n - (size_t)start;
    char* substr = malloc(size);
    size_t i;

    for (i = 0; i < size - 1; i++){
        substr[i] = aStr[start + i - 1];
    }

    substr[i] = '\0';

    return substr;
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

int traverse_dir(char* dir_name, struct dirinfo dir_info[]){
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
            struct dirinfo* cur_dir = &dir_info[i++];
            snprintf(cur_dir->dir_name, sizeof(cur_dir->dir_name), "%s/%s", dir_name, ent->d_name);
            cur_dir->dir_ent = *ent;
        } 
    }

    closedir(dir);

    return 0;
}