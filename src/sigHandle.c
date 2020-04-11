#include "sigHandle.h"

extern pid_t pid_child;

void SIGTERM_handler(int signal){
    recv_sig_log("SIGTERM");
    exit_log(10);
}

void SIGCONT_handler(int signal){
    recv_sig_log("SIGCONT");
}

void SIGSTOP_handler(int signal){
    recv_sig_log("SIGSTOP");
    pause();
}

void SIGINT_handler(){
    recv_sig_log("SIGINT");

    if (pid_child){
        send_sig_log(pid_child, "SIGSTOP");
        kill(pid_child, SIGSTOP);
    }

    printf("Pretende terminar o programa (T) ou continuar a sua execução (C)?\n");

    char answer[1];
    bool invalid_answer = true;
    
    while (invalid_answer){
        read(STDIN_FILENO, answer, 1);

        if (strcmp(answer, "T") == 0){
            invalid_answer = false;

            send_sig_log(pid_child, "SIGCONT");
            send_sig_log(pid_child, "SIGTERM");
            
            kill(pid_child, SIGCONT);
            kill(pid_child, SIGTERM);            
        }
        else if (strcmp(answer, "C") == 0){
            invalid_answer = false;

            send_sig_log(pid_child, "SIGCONT");
            kill(pid_child, SIGCONT);
        }
        else
            printf("Resposta invalida, tente outra vez (T/C)\n");
    }
    
}

