#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

typedef struct tree_node{
    int children_no;
    struct tree_node* child1;
    struct tree_node* child2;
    char nodeName;
}tree_node;

void createTree(char Root, int children_no, char child1, char child2){
    int x = children_no;
    
    printf("Root: %d\n", getpid());

    if(child2 == '-'){
    	x == 1;
    }

    if(x == 1){
        pid_t pid1 = fork();
        if (pid1 == 0) {
            printf("B: child pid: %d\tparent pid: %d\n",getpid(), getppid());
        }
        else if (pid1 > 0){
            printf("A: child pid: %d\tparent pid: %d\n",getpid(), getppid());
        }
    }
    

    pid_t pid2 = fork() && fork();
    
    if(x == 2){
        if (pid2 == 0) {
            printf("A: child pid: %d\tparent pid: %d\n",getpid(), getppid());
            exit(1);
        }
        else if (pid2 > 0){
            printf("A: child pid: %d\tparent pid: %d\n",getpid(), getppid());
            exit(1);
        }
    }
    //createTree(Root, children_no, child1, child2);
}

void read_tree_file(const char* filename){

	// File* file = fopen("Input_Problem2.txt","r");

	// char buffer[10000];
	// fgets(buffer, 10000, file);

	// tree_node *Root;
	// tree_node *current;

	// Root = malloc(sizeof(tree_node));

	// char *token = strtok(buffer, " ");

	// tree_node *Root = malloc(sizeof(tree_node));
	// Root->children_no = 1;
	// Root->nodeName = 'B';

	// createTree()

}

int main(){

	createTree('A', 2, 'B', 'C');
	createTree('B', 1, 'D', '-');
	return 0;
}