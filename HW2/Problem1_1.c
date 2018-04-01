#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>

void* sequence(); 

int *array; 

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
	if (fib == 1)
	{
		printf("Fibonacci Sequence: "); 
		printf("%d %d", 0, 1); 
		return 0; 
	}
	
	array = malloc(sizeof(int) * (fib+1));  
	array[0] = 0; 
	array[1] = 1; 
	
	pthread_t tid; 
	pthread_attr_t attr;
	pthread_attr_init(&attr);
	pthread_create(&tid, &attr,sequence, fib);    
	
	pthread_join(tid, NULL); 
	
	printf("Fibonacci Sequence: "); 
	for(int i = 0; i <= fib; i++)
	{
		printf("%d ", array[i]); 
	}
}

void* sequence(int fib)
{
	for (int i = 2; i <= (fib); i++)
	{
		array[i] = array[i-1] + array[i-2]; 
	}
	pthread_exit(0); 
}
