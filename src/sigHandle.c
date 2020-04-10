#include "logHandle.h"
#include <signal.h>

void SIGTERM_handler(){
    recv_sig_log("SIGTERM");
    exit_log(3);

}

void SIGCONT_handler(){
    recv_sig_log("SIGCONT");
}

void SIGTSTP_handler(){
    recv_sig_log("SIGTSTP");
    pause();
}

void SIGINT_handler(){
    recv_sig_log("SIGINT");

    //need to suspend
    

    pid_t pid = getpid();
    send_sig_log(pid, "SIGTSTP");
    raise(SIGTSTP);
    

    printf("Pretende terminar o programa (T) ou continuar a sua execução (C)?\n");

    char answer[1];
    bool invalid_answer = true;

    
    while(invalid_answer){
        read(STDIN_FILENO,answer,1);

        if(strcmp(answer, "T") == 0){
            invalid_answer = false;
            //terminate
            send_sig_log(pid, "SIGTERM");
            
            //raise(SIGTERM);

            //signal(SIGTERM, SIGTERM_handler);
            
        }
        else if(strcmp(answer, "C") == 0){
            invalid_answer = false;
            //continue
            send_sig_log(pid, "SIGCONT");
            //signal(SIGCONT, SIGCONT_handler);
            //raise(SIGCONT);
        }
        else{
            printf("Resposta invalida, tente outra vez (T/C)\n");
        }
    }
    
}

