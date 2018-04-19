#include <pthread.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdio.h>
#include <signal.h>
#include <stdbool.h>
#include "CycleTimer.h"

typedef struct data{
	char name[10];
	double age;
} data;

int alrmflag = 0;
volatile int lock = 1;

void sig_func(int sig){
	printf("Caught signal no = %d\n", sig);
	signal(sig,sig_func);
}

void sig_func2(int sig){
	printf("Caught signal no = %d\n", sig);
	alrmflag = 1;
}

void func(data *p){
	int x;

	snprintf(p->name, 10, "%d", (int)pthread_self());
	p->age = currentSeconds();

	x = (int)(((int)pthread_self() + getpid())/((getpid()*(int)test_and_set(&lock))));
	sleep(50);
}

int test_and_set(int *target){
	int rv = *target;
	*target = 1;

	return rv;
}

int main(){
	pthread_t tid1, tid2, tid3;
	pthread_attr_t attr;
	data d;
	data *ptr = &d;
	int pid;
	int lock = 0;
	int err;

	signal(SIGINT, SIG_IGN); //Ignore Signal - The signal is ignored
	err = pthread_create(&tid3, NULL, (void*)func, &ptr);
	signal(SIGSEGV, sig_func);
	signal(SIGSTOP, sig_func);
	err = pthread_create(&tid2, NULL, (void*)func, &ptr);
	signal(SIGFPE, sig_func);
	signal(SIGALRM, sig_func2);
	signal(SIGINT, sig_func2);
	err = pthread_create(&tid1, NULL, (void*)func, &ptr);

	sleep(10);

	//printf("All three threads are created.\n");

	pid = getpid();
	sleep(10);
	pthread_kill(tid1, SIGSEGV);
	sleep(5);
	pthread_kill(tid2, SIGSTOP);
	alarm(3);
	while(!alrmflag) pause();

	// kill(pid, SIGINT);
	// kill(pid, SIGINT);
	// kill(pid, SIGINT);
	// kill(pid, SIGINT);
	// kill(pid, SIGINT);

	// kill(pid, SIGSEGV);
	// kill(pid, SIGSEGV);
	// kill(pid, SIGSEGV);
	// kill(pid, SIGSEGV);
	// kill(pid, SIGSEGV);

	// kill(pid, SIGQUIT);
	// kill(pid, SIGQUIT);
	// kill(pid, SIGQUIT);
	// kill(pid, SIGQUIT);
	// kill(pid, SIGQUIT);

	// kill(pid, SIGSTOP);
	// kill(pid, SIGSTOP);
	// kill(pid, SIGSTOP);
	// kill(pid, SIGSTOP);
	// kill(pid, SIGSTOP);

	// kill(pid, SIGKILL);
	// kill(pid, SIGKILL);
	// kill(pid, SIGKILL);
	// kill(pid, SIGKILL);
	// kill(pid, SIGKILL);

	pthread_kill(tid1, SIGINT);
	pthread_kill(tid3, SIGINT);
	sleep(40);
	pthread_join(tid1, NULL);
	pthread_join(tid2, NULL);
	pthread_join(tid3, NULL);
}