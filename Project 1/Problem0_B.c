#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
    
    int min=0;
    int max=0;
    int sum=0;
    int i;
    
    FILE *file1 = fopen("Input_Problem0_A.txt", "r");
    
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
    
    pid_t pid2 = fork();
    if(pid2 == 0){
        for(i = 0; i < size; i++){
            sum += arrNum[i];
        }
        printf("Hi I am Process 2 and my pid is %d. My Parent's pid is %d\n",getpid(),getppid());
        int status;
        waitpid(pid2, &status, 0);
        
        printf("sum=%d\n", sum);
        
    }
    else if (pid2 > 0){
        if(arrNum[0] > arrNum[1]){
            max = arrNum[0];
            min = arrNum[1];
        }else{
            max = arrNum[1];
            min = arrNum[0];
        }
        
        for(i = 0; i < size; i++){
            
            if(max < arrNum[i]){
                max = arrNum[i];
            }
            
            else if(min > arrNum[i]){
                min = arrNum[i];
            }
        }
        printf("Hi I am Process 1 and my pid is %d. I am the Parent.\n",getpid());
        int status;
        waitpid(pid2, &status, 0);
        
        printf("max=%d\n", max);
        printf("min=%d\n", min);
    }
    
    fclose (file1);
    return 0;
}
