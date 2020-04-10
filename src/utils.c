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
    size_t i, length = n - (size_t)start;
    char* substr = malloc(length);

    for (i = 0; i < length + 1; i++){
        substr[i] = aStr[start + i - 1];
    }

    return substr;
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

