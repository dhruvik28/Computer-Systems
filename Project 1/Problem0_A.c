#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(){
    
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
    
    if(arrNum[0] > arrNum[1]){
        max = arrNum[0];
        min = arrNum[1];
    }else{
        max = arrNum[1];
        min = arrNum[0];
    }
    
    for(i = 0; i < size; i++){
        sum += arrNum[i];
        
        if(max < arrNum[i]){
            max = arrNum[i];
        }
        
        if(min > arrNum[i]){
            min = arrNum[i];
        }
    }
    
    
    printf("max=%d\n", max);
    printf("min=%d\n", min);
    printf("sum=%d\n", sum);
    
    fclose (file1);
    
    return 0;
}
