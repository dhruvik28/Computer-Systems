#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    printf("The root is: %d\n", getpid());
    pid_t pid1 = fork() && (fork() || fork());
    if (pid1 > 0)
    {
        //        fork() && fork();
        //        printf("C's pid is: %d      C's Parents pid is: %d\n", getpid(), getppid());
        //        printf("%d\n%d\n", getpid(), getppid());
    }
    
    printf("child pid %d    parent pid %d\n", getpid(), getppid());
    
    fflush(stdout);
    
    sleep(10);
    
    return 0;
}
