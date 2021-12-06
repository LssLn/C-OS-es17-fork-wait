#include <sys/types.h>
#include <sys/wait.h>
#include <stdio.h>
#include <unistd.h>

int main(){
    pid_t pid;
    char * message;
    int n, stat_val, exit_code;

    pid=fork();
    switch(pid){
        case -1:
            perror("fork failed\n");
            exit(1);
        case 0:
            message="Child";
            n=5;
            exit_code=37;
            break;
        default:
            message="Father";
            n=3;
            exit_code=0;
            break;
    }

    for(;n>0;n--){
        puts(message);
        sleep(1);
    }

    if(pid!=0){
        //questo codice viene eseguito solo dal padre
        pid_t child_pid;
        child_pid = wait(&stat_val); //è bloccante
        //cioè fino a quando non finisce il child, non va avanti
        printf("Child has finished: PID %d\n",child_pid);
        if(WIFEXITED(stat_val)) //cio+ se !=0, cioè tutto normale
            printf("Child exited with code %d\n",WEXITSTATUS(stat_val)); //wexitstatus si usa solo se wifexited != 0
        else //wifexited ==0, abnormally
            printf("Child terminanted abnormally\n");
    }

    exit(exit_code);
}

/* WIFEXITED(stat_val) è non nullo se il figlio ha terminato normalmente. La macro WIFEXITED(stat_val) è definita in sys/wait.h*/
/*la macro WEXITSTATUS restituisce il codice di exit del figlio se questo ha terminato normalmente. Si usa solo se WIFEXITED ritorna un valore non nullo */
