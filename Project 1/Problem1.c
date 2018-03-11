#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

int main(void) {
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    
    printf("The root is: %d\n", getpid());
    
    int fd1[2],status;
    pipe(fd1);
    
    pid_t pid1 = fork();
    if (pid1 == 0)
    {
        close(fd1[0]);
        
        b = 9;
        printf("Process C with pid: %d and parent pid %d\n", getpid(), getppid());
        write(fd1[1], &b, sizeof(b));
        close(fd1[1]);
        exit(0);
        
    }
    else {
        waitpid(pid1, &status, status);
        
        close(fd1[1]);
        read(fd1[0], &b, sizeof(b));
        a = 5;
        printf("Process A with pid: %d and is the parent\n", getpid());
        close(fd1[0]);
        
    }
    
    int fd2[2];
    pipe(fd2);
    
    pid_t pid2 = fork();
    if (pid2 == 0)
    {
        close(fd2[0]);
        
        d = 12;
        printf("Process B with pid: %d and parent pid %d\n", getpid(), getppid());
        pid_t pid3 = fork();
        if (pid3 == 0){
            printf("Process D with pid: %d and parent pid %d\n", getpid(), getppid());
            exit(0);
        }
        
        write(fd2[1], &d, sizeof(d));
        close(fd2[1]);


        exit(0);
        
    }
    else {
        waitpid(pid2, &status, status);
        close(fd2[1]);
        read(fd2[0], &d, sizeof(d));
        c = 8;
        close(fd2[0]);
        
    }
    
    printf("A = %d, B = %d, C = %d, D = %d.\n", a,b,c,d);
    
    
    // printf("child pid %d    parent pid %d\n", getpid(), getppid());
    
    fflush(stdout);
    
    sleep(10);
    
    return 0;
}
