#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

int main(){
    
    int min=0;
    int max=0;
    int sum=0;
    int i;
    
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
    
    int fd1[2];
    pipe(fd1);
    
    pid_t pid2 = fork();
    if(pid2 == 0){
        close(fd1[0]);

        for(i = 0; i < size; i++){
            sum += arrNum[i];
        }
        printf("Hi I am Process 2 and my pid is %d. My Parent's pid is %d\n",getpid(),getppid());
        //printf("sum=%d\n", sum);
        write(fd1[1], &sum, sizeof(sum));
        close(fd1[1]);
        exit(0);
    }
    else{
        close(fd1[1]);
        read(fd1[0], &sum, sizeof(sum));
        int status;
        waitpid(pid2, &status, 0);
        close(fd1[0]);
    }
  //  printf("Hi I am Process 1 and my pid is %d. I am the Parent.\n", getpid());
    
    pid_t pid3 = fork();
    if (pid3 == 0){
        if(arrNum[0] > arrNum[1]){
            max = arrNum[0];
            min = arrNum[1];
        }else{
            max = arrNum[1];
            min = arrNum[0];
        }
        printf("Hi I am Process 3 and my pid is %d. My Parent's pid is %d\n", getpid(), getppid());
        
        pid_t pid4 = fork();
        if(pid4 == 0){
            printf("Hi I am Process 4 and my pid is %d. My Parent's pid is %d\n", getpid(), getppid());
            for(i = 0; i < size; i++){
                
                if(max < arrNum[i]){
                    max = arrNum[i];
                }
            }
            printf("Max=%d\n", max);
            exit(0);
            
        }else{
            for(i = 0; i < size; i++){
                
                if(min > arrNum[i]){
                    min = arrNum[i];
                }
            }
            int status;
            waitpid(pid4, &status, 0);
            printf("Min=%d\n", min);
        }
        exit(0);
    }
    else {
        
        int status1;
        waitpid(pid3, &status1, 0);
    }
    printf("Sum=%d\n", sum);
    
    fclose (file1);
    
    return 0;
}