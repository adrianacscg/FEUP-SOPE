#include "instructions.c"

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

int parseCommand(char* cmdArg){
    int cmd;

    if (strcmp(cmdArg, "-H")  == 0 || strcmp(cmdArg, "--help")  == 0)
        cmd = HELP;
    else if (strcmp(cmdArg, "-a") == 0 || strcmp(cmdArg, "--all") == 0)
        cmd = ALL;
    else if (strcmp(cmdArg, "-b") == 0 || strcmp(cmdArg, "--bytes") == 0)
        cmd = BYTES;
    else if (strcmp(cmdArg, "-B") == 0 || strcmp(cmdArg, "--block-size") == 0)
        cmd = BLOCK_SIZE;
    else if (strcmp(cmdArg, "-l") == 0 || strcmp(cmdArg, "--count-links") == 0)
        cmd = COUNT_LINKS;
    else if (strcmp(cmdArg, "-L") == 0 || strcmp(cmdArg, "--dereference") == 0)
        cmd = DEREF;
    else if (strcmp(cmdArg, "-S") == 0 || strcmp(cmdArg, "--separate-dirs") == 0)
        cmd = SEP_DIRS;
    else if (strcmp(cmdArg, "--max-depth") == 0)
        cmd = MAX_DEPTH;
    else 
        cmd = INVALID_COMMAND;

    return cmd;
}

int main(int argc, char* argv[]){
    
    if (argc > 2) {
        int cmd = parseCommand(argv[2]);

        switch (cmd){
            case ALL: {
                break;
            }
            case BYTES: {
                break;
            }
            case BLOCK_SIZE: {
                break;
            }
            case COUNT_LINKS: {
                break;
            }
            case SEP_DIRS: {
                break;
            }
            case MAX_DEPTH: {
                break;
            }
            case HELP: {
                char line_1[] = "List of commands:\n";
                char line_2[] = "\t• -a, --all – a informação exibida diz respeito também a ficheiros;\n";
                char line_3[] = "\t• -b, --bytes – apresenta o número real de bytes de dados (ficheiros) ou alocados (diretórios);\n";
                char line_4[] = "\t• -B, --block-size=SIZE – define o tamanho (bytes) do bloco para efeitos de representação;\n";
                char line_5[] = "\t• -l, --count-links – contabiliza múltiplas vezes o mesmo ficheiro;\n";
                char line_6[] = "\t• -L, --dereference – segue links simbólicos;\n";
                char line_7[] = "\t• -S, --separate-dirs – a informação exibida não inclui o tamanho dos subdiretórios;\n";
                char line_8[] = "\t• --max-depth=N – limita a informação exibida a N (0,1, …) níveis de profundidade de diretórios.\n";

                char help_msg[BUFFER_SIZE];
                char* lines[8] = {line_1, line_2, line_3, line_4, line_5, line_6, line_7, line_8};                
                
                for (size_t i = 0; i < ARRAY_SIZE(lines); i++)
                    strcat(help_msg, lines[i]);
                    
                int len = strlen(help_msg);

                write(STDOUT_FILENO, help_msg, len);

                break;
            }
            default: {
                char error_msg[] = "Invalid command line argument.\nType --help or -H to get a list of possible input flags.\n";
                int len = strlen(error_msg);
                
                write(STDERR_FILENO, error_msg, len);
                
                exit(1);
            }
        }
    } else {

    }

    return 0;
}