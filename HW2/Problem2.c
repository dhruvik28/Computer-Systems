#include<stdio.h>
#include<string.h>
#include<pthread.h>
#include<stdlib.h>
#include<unistd.h>
#include<stdbool.h>
#include<math.h>

void *thread1_solution();
void *thread2_solution();
int reverseInt(int);
int max_reverse();
int n; 
bool *array; 
bool *array2; 
int main()
{
	printf("Please enter n: "); 
	scanf("%d", &n);
	
	if (n <= 1)
	{
		printf("Error, not a valid input"); 
		return 0; 
	}
	
	array = malloc(sizeof(bool)*(n+1)); 
	for(int i = 2; i <=n; i++)
	{
		array[i] = true; 
	}
	
	pthread_t tid1; 
	pthread_attr_t attr1;
	pthread_attr_init(&attr1);
	pthread_create(&tid1, &attr1,thread1_solution, NULL); 

	pthread_join(tid1, NULL); 
	
	pthread_t tid2; 
	pthread_attr_t attr2;
	pthread_attr_init(&attr2);
	pthread_create(&tid2, &attr2,thread2_solution, NULL); 
	
	pthread_join(tid2, NULL);

	return 0; 
	
	
}

void *thread1_solution()
{
	int square_root = floor(sqrt(n)); 
	for(int i = 2; i <= square_root; i++)
	{
		if (array[i] == true);
		{
			for(int j = pow(i,2); j <= n; j = j + i)
			{
				array[j] = false; 
			}		
		}	
	}
	
	printf("List of primes: "); 
	for(int i = 2; i <= n; i++)
	{
		if (array[i] == true) 
		{
			printf("%d ", i); 
		}
	}
	
	pthread_exit(0); 
	
}

void *thread2_solution()
{
	
	int max = max_reverse(); 
	array2 = malloc(sizeof(bool)*(max+1)); 
	for(int i = 2; i <=max; i++)
	{
		array2[i] = true; 
	}
	int square_root = floor(sqrt(max)); 
	for(int i = 2; i <= square_root; i++)
	{
		if (array2[i] == true);
		{
			for(int j = pow(i,2); j <= max; j = j + i)
			{
				array2[j] = false; 
			}		
		}	
	}
	
	printf("\nList of primes with reverse digit prime symmetry: ");  
	int reverse; 
	for(int i = 2; i <= n; i++)
	{
		reverse = reverseInt(i);
		if (array2[i] == true && array2[reverse] == true)
		{
			printf("%d ", i); 
		}
	}
	pthread_exit(0); 
}

int max_reverse()
{
	int max = n; 
	for(int i = 2; i <=n; i++)
	{
		if (max < reverseInt(i))
		{
			max = reverseInt(i); 
		}
	}
	return max; 
}

int reverseInt(int i)
{
	int reverse = 0; 
	if(i < 10) return i; 
	while(i != 0)
	{
		reverse = reverse * 10;
		reverse = reverse + i%10;
		i = i/10;		
	}
	return reverse; 
}