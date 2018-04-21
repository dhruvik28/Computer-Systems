#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

void handler1(int signum, siginfo_t *info, void *extra)
{
    void *ptr_val = info->si_value.sival_ptr;
    int int_val = info->si_value.sival_int;
    printf("Min=%d\n",int_val);
}

void handler2(int signum, siginfo_t *info, void *extra)
{
    void *ptr_val = info->si_value.sival_ptr;
    int int_val = info->si_value.sival_int;
    printf("Max=%d\n",int_val);
}

void handler3(int signum, siginfo_t *info, void *extra)
{
    void *ptr_val = info->si_value.sival_ptr;
    int int_val = info->si_value.sival_int;
    printf("Sum=%d\n",int_val);
}

int main(){
    
    int min=0;
    int max=0;
    int sum=0;
    int i, status;
    
    FILE *file1 = fopen("Input_Problem0.txt", "r");
    
    int size = 1;
    int ch = 0;
    
    if(file1 == NULL){
        printf("no numbers in the input file \n");
    }
    
    while(!feof(file1)){
        
        ch = fgetc(file1);
        if(ch == '\n'){
            size++;
        }
    }
    int arrNum[size];
    
    rewind(file1);
    
    for (i = 0; i < size; i++)
    {
        fscanf(file1, "%d", &arrNum[i]);
    }
    
    if(size == 1){
        printf("Max = %d\n", arrNum[0]);
        printf("Min = %d\n", arrNum[0]);
        printf("Sum = %d\n", arrNum[0]);
        return 0;
    }
    
    pid_t pid1 = fork();
    if (pid1 == 0){
        wait(&status);
        if(arrNum[0] > arrNum[1]){
            max = arrNum[0];
            min = arrNum[1];
        }else{
            max = arrNum[1];
            min = arrNum[0];
        }
        printf("Hi I am Process 2 and my pid is %d. My Parent's pid is %d\n", getpid(), getppid());
        
        pid_t pid2 = fork();
        if(pid2 == 0){
            wait(&status);
            printf("Hi I am Process 3 and my pid is %d. My Parent's pid is %d\n", getpid(), getppid());
            for(i = 0; i < size; i++){
                
                if(max < arrNum[i]){
                    max = arrNum[i];
                }
            }

            pid_t pid3 = fork();
            if(pid3 == 0){
                alarm(1);  
                wait(&status);
                printf("Hi I am Process 4 and my pid is %d. My Parent's pid is %d\n",getpid(),getppid());
                for(i = 0; i < size; i++){
                
                    if(min > arrNum[i]){
                        min = arrNum[i];
                    }
                }
                sigqueue(getppid(),SIGUSR1,(const union sigval) min);
                
                exit(0);
            } else{
                struct sigaction action1;
                sigset_t mask1;
                sigemptyset(&mask1);
                sigaddset(&mask1,SIGUSR1);
                action1.sa_flags = SA_SIGINFO;
                action1.sa_mask =mask1;
                action1.sa_sigaction = &handler1;

                if (sigaction(SIGUSR1,&action1,NULL)==-1) {
                    perror("sigaction");
                    exit(EXIT_FAILURE);
                }
                wait(&status);   
            }
            sigqueue(getppid(),SIGUSR1,(const union sigval) max);

            exit(0);
        }else{
            struct sigaction action2;
            sigset_t mask2;
            sigemptyset(&mask2);
            sigaddset(&mask2,SIGUSR1);
            action2.sa_flags = SA_SIGINFO;
            action2.sa_mask =mask2;
            action2.sa_sigaction = &handler2;

            if (sigaction(SIGUSR1,&action2,NULL)==-1) {
                perror("sigaction");
                exit(EXIT_FAILURE);
            }
            wait(&status);
        }
        for(i = 0; i < size; i++){
            sum += arrNum[i];
        }
        sigqueue(getppid(),SIGUSR1,(const union sigval) sum);

        exit(0);
    }
    else {
        struct sigaction action3;
        sigset_t mask3;
        sigemptyset(&mask3);
        sigaddset(&mask3,SIGUSR1);
        action3.sa_flags = SA_SIGINFO;
        action3.sa_mask =mask3;
        action3.sa_sigaction = &handler3;

        if (sigaction(SIGUSR1,&action3,NULL)==-1) {
            perror("sigaction");
            exit(EXIT_FAILURE);
        }
        wait(&status);
    }

    fclose (file1);
    
    return 0;
}