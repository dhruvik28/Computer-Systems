//
//  main.c
//  Computer Systems Problem 0
//
//  Created by Michael Zheng on 2/22/18.
//  Copyright © 2018 Michael Zheng. All rights reserved.
//

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>

/*void explain_wait_status(pid_t pid, int status)
{
    if (WIFSTOPPED(status))
        fprintf(stderr, "Child with PID = %ld has been stopped by a signal, signo = %d\n", (long)pid, WSTOPSIG(status));
    else if (WIFSIGNALED(status))
        fprintf(stderr, "Child with PID = %ld was terminated by a signal, signo = %d\n", (long)pid, WTERMSIG(status));
    else if (WIFEXITED(status))
        fprintf(stderr, "Child with PID = %ld terminated normally, exit status = %d\n", (long)pid, WEXITSTATUS(status));
    else {
        fprintf(stderr, "%s: Internal error: Unhandled case, PID = %ld, status = %d\n", __func__, (long)pid, status);
        exit(1);
    }
    fflush(stderr);
}

void sigchild_handler(int signum)
{
    pid_t p;
    int status;
    
    do {
        p = waitpid(-1, &status, WUNTRACED | WNOHANG);
        if (p < 0) {
            perror("waitpid");
            exit(1);
        }
        explain_wait_status(p, status);
        
        if (WIFEXITED(status) || WIFSIGNALED(status)){
            
        }
        
        if (WIFSTOPPED(status)){
            
        }
        
    } while (p > 0);
}

void wait_for_children()
{
    pid_t p;
    int status;
    
    explain_wait_status(p, status);
    wait(NULL);
}

typedef struct tree_node{
    int children_no;
    struct tree_node* left;
    struct tree_node* right;
    char* nodeNameLeft;
    char* nodeNameRight;
    char* nodeName;
}tree_node;


tree_node* newNode(int children_no, char* nodeName){
    
    tree_node* node = (tree_node*)malloc(sizeof(tree_node));
    
    node->children_no = children_no;
    node->nodeName = nodeName;
    
    node->left = NULL;
    node->right = NULL;
    
    return node;
}


void createTree(tree_node* root, int children_no, char* nodeNameLeft, char* nodeNameRight){
    
    if(children_no == 1){

        pid_t pid1 = fork();
        pid_t wpid1;
        int status1 = 0, status;
        if(pid1 == 0){

            printf("Node %s: Child: %d, Parent: %d\n", nodeNameLeft, getpid(), getppid());
            
            while((root->left) != NULL){
                root = root->left;
            }
            
            tree_node* node = newNode(0, "D");
            node->left = NULL;
            node->right = NULL;
            
            root->left = node;
            root->nodeNameLeft = (char*)nodeNameLeft;
            
//            raise(SIGSTOP);
//            waitpid(pid1, &status, WUNTRACED);
//            explain_wait_status(pid1, status);
            
            exit(1);
            
        }else if(pid1 > 0){
//            kill(pid1, SIGSTOP);
//            waitpid(pid1, &status, WUNTRACED);
//            explain_wait_status(pid1, status);
            while((wpid1 = wait(&status1)) > 0);

        }
        //return createTree(root, 2, "B", "C");
        return;
    }
    
    
    if(children_no == 2){
        
        pid_t pid2 = fork();
        pid_t wpid2;
        int status2 = 0, status;
        
        
        if(pid2 == 0){
            
            while((root->left) != NULL){
                root = root->left;
            }
            printf("Node %s: Child: %d, Parent: %d\n", nodeNameLeft, getpid(), getppid());
            tree_node* node = newNode(0, "B");
            node->left = NULL;
            node->right = NULL;
            
            
            root->left = node;
            root->nodeNameLeft = (char*)nodeNameLeft;
            
//            raise(SIGSTOP);
//            waitpid(pid2, &status, WUNTRACED);
//            explain_wait_status(pid2, status);
            
            exit(1);
        }else {
//            kill(pid2, SIGSTOP);
//            waitpid(pid2, &status, WUNTRACED);
//            explain_wait_status(pid2, status);
            while((wpid2 = wait(&status2)) > 0);
        }
        
        int fd1[2];
        pipe(fd1);
        
        pid_t pid3 = fork();
        pid_t wpid3;
        int status3 = 0;
        if(pid3 == 0){
            close(fd1[0]);
            
            printf("Node %s: Child: %d, Parent: %d\n", nodeNameRight, getpid(), getppid());
            tree_node* node1 = newNode(0, "C");
            node1->left = NULL;
            node1->right = NULL;
            
            while((root->right) != NULL){
                root = root->right;
            }
            
            root->right = node1;
            root->nodeNameRight = (char*)nodeNameRight;
            
//            raise(SIGSTOP);
//            waitpid(pid2, &status, WUNTRACED);
//            explain_wait_status(pid2, status);
            
            exit(1);
        }else{
//            kill(pid3, SIGSTOP);
//            waitpid(pid3, &status, WUNTRACED);
//            explain_wait_status(pid3, status);
            while((wpid3 = wait(&status3)) > 0);
        }
        
        return createTree(root, 1, "D", "-");
        
    }
    
    // int x = children_no;
    
    // printf("Root: %d\n", getpid());
    
    // if(child2 == '-'){
    // 	x == 1;
    // }
    // if(x == 1){
    //     pid_t pid1 = fork();
    //     if (pid1 == 0) {
    //         printf("B: child pid: %d\tparent pid: %d\n",getpid(), getppid());
    //         exit(1);
    //     }
    //     else if (pid1 > 0){
    //         printf("A: child pid: %d\tparent pid: %d\n",getpid(), getppid());
    //     }
    // }
    
    
    // pid_t pid2 = fork() && fork();
    
    // if(x == 2){
    //     if (pid2 == 0) {
    //         printf("A1: child pid: %d\tparent pid: %d\n",getpid(), getppid());
    //         exit(1);
    //     }
    //     else if (pid2 > 0){
    //         printf("A2: child pid: %d\tparent pid: %d\n",getpid(), getppid());
    
    //     }
    // }
    //createTree(Root, children_no, child1, child2);
}*/

// void read_tree_file(const char* filename){

// 	// File* file = fopen("Input_Problem2.txt","r");

// 	// char buffer[10000];
// 	// fgets(buffer, 10000, file);

// 	// tree_node *Root;
// 	// tree_node *current;

// 	// Root = malloc(sizeof(tree_node));

// 	// char *token = strtok(buffer, " ");

// 	// tree_node *Root = malloc(sizeof(tree_node));
// 	// Root->children_no = 1;
// 	// Root->nodeName = 'B';

// 	// createTree()

// }*/


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
        waitpid(pid2, &status, NULL);
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
            waitpid(pid4, &status, NULL);
            printf("Min=%d\n", min);
        }
        exit(0);
    }
    else {
        
        int status1;
        waitpid(pid3, &status1, NULL);
    }
    printf("Sum=%d\n", sum);
    
    fclose (file1);
    
    /*    int value = 0;
     int ko, status;
     
     int fd1[2];
     pipe(fd1);
     
     pid_t pid = fork();// && (fork() || fork());
    
     if (pid == 0) {
//     signal(SIGSTOP, sigchild_handler);

         
     close(fd1[0]);

     value = 3;
     
     write(fd1[1], &value, sizeof(value));
     close(fd1[1]);
    
//     signal(SIGSTOP, sigchild_handler);

     exit(0);
     }
     else{
     kill(pid, SIGSTOP);
     waitpid(pid,&status,WUNTRACED);
     explain_wait_status(pid, status);
     kill(pid, SIGCONT);



     close(fd1[1]);
     read(fd1[0], &value, sizeof(value));
     ko = 4;
     close(fd1[0]);

     }
    explain_wait_status(pid, status);



     printf("%d, %d\n", value, ko);*/

    //createTree('A', 2, 'B', 'C');
    //createTree('B', 1, 'D', '-');
    
    /*printf("Root: %d\n", getpid());
    fflush(stdout);
    
    tree_node* root = newNode(0, "Root");
    if(root == NULL){
        root->nodeName = "Root";
    }
    
    printf("%s\n", root->nodeName);
    
    createTree(root, 2, "B", "C");*/
    //createTree(root, 1, "D", "-");
    
    //sleep(3);
    //printf("%s\n", root->nodeNameLeft);
    
    //getchar();
    
    /*int value = 0;
    int ko;
    
    int fd1[2];
    pipe(fd1);
    
    pid_t pid = fork();
    if (pid == 0) {
        
        close(fd1[0]);
        value = 3;

        write(fd1[1], &value, sizeof(value));
        close(fd1[1]);


        exit(0);
    }
    else{
        close(fd1[1]);
        read(fd1[0], &value, sizeof(value));
        ko = 4;
        close(fd1[0]);
    }
    
    int fd2[2];
    pipe(fd2);
    
    pid_t pid1 = fork();
    if (pid1 == 0) {
        
        close(fd2[0]);
        value += 3;
        
        write(fd2[1], &value, sizeof(value));
        close(fd2[1]);
        
        
        exit(0);
    }
    else{
        close(fd2[1]);
        read(fd2[0], &value, sizeof(value));
        ko += 4;
        close(fd2[0]);
    }
    
    
    printf("%d, %d\n", value, ko);*/





//    printf("X: child pid%d\tparent pid: %d\n",getpid(), getppid());

/*//    printf("root %d\n", getpid());
 printf("The root is: %d\n", getpid());
 pid_t pid1 = fork() && (fork() || fork());
    if (pid1 == 0)
    {
        fork();
//        fork() && fork();
//        printf("C's pid is: %d      C's Parents pid is: %d\n", getpid(), getppid());
//        printf("%d\n%d\n", getpid(), getppid());
    }
    else
    {
        c=fork();
        if(c==0){
            g=fork();
            if(g==0)
                printf("B's pid is: %d      B's Parents pid is: %d\n", getpid(), getppid());
            else
                printf("D's pid is: %d      D's Parents pid is: %d\n", getpid(), getppid());
        }
        else
            printf("The root is: %d\n", getppid());
            printf("A's pid is: %d      A's Parents pid is: %d\n", getpid(), getppid());
    }   else {
        if (fork())
        {
            fork();
        }
    }
    
    printf("child pid %d    parent pid %d\n", getpid(), getppid());
    
    fflush(stdout);
    
    sleep(10);*/
    
    return 0;
}
