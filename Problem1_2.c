#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>

void* sequence(); 

int *array; 
bool ready = false; 

int main()
{
	int fib; 
	printf("Please enter Fibonacci number: "); 
	scanf("%d", &fib); 

	if (fib < 0) 
	{
		printf("Error, not a valid input"); 
		return 0; 
	}
	
	if (fib == 0)
	{
		printf("Fibonacci Sequence: "); 
		printf("%d", 0); 
		return 0; 
	}

	printf("Fibonacci Sequence: "); 
	printf("%d %d ", 0, 1); 

	array = malloc(sizeof(int) * (fib+1));  
	array[0] = 0; 
	array[1] = 1; 
	
	pthread_t tid; 
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr,sequence, fib);    

	for(int i = 2; i <= fib; i++)
	{
		while(ready == false); 
		printf("%d ", array[i]); 
		ready = false; 
	}
	
	pthread_join(tid, NULL); 
}

void* sequence(int fib)
{
	for (int i = 2; i <= (fib); i++)
	{
		while(ready == true); 
		array[i] = array[i-1] + array[i-2]; 
		ready = true;  
	}
	pthread_exit(0); 
}
