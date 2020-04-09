#include "instructions.h"

int parse_command(char* cmdArg, struct cmdfl* cmd_flags){

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
    /* This is useless, not sure if it might be usefull later tho so that's why I didn't delete it and decided to make a comment so you can then read this really long unnecessary comment that says something obvious and laugh and come give me a kiss because you read all this way even tho you hate comments and I love you :)
    else if (strcmp(cmdArg, "-l") == 0 || strcmp(cmdArg, "--count-links") == 0){
        //cmd = COUNT_LINKS;
        cmd_flags->count_links = true;
    }*/
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

    return 0;
}