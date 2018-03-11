#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct tree_node{
    char* children_no;
    struct tree_node* left;
    struct tree_node* right;
    char* nodeNameLeft;
    char* nodeNameRight;
    char* nodeName;
    int pid;
    int ppid;

   struct tree_node* next;
};

void createTree(struct tree_node* ptr);
void read_tree_file(const char* filename);
void print_tree(struct tree_node* root);

struct tree_node *root = NULL;

void createTree(struct tree_node* ptr){

	struct tree_node *current = malloc(sizeof(struct tree_node));
	//ptr = malloc(sizeof(struct tree_node));


	current = root;

	if(strcmp(ptr->children_no, "2") == 0){

		int pid;
		int ppid;
		char* name;

		struct tree_node* node = malloc(sizeof(struct tree_node));

		int fd1[2];
		pipe(fd1);

		pid_t pid2 = fork();
		pid_t wpid2;
		int status2 = 0;

		if(pid2 == 0){		

			printf("Node %s: Pid: %d, ParentPid: %d\n", ptr->nodeNameLeft, getpid(), getppid());

			close(fd1[0]);
			name = ptr->nodeNameLeft;
			pid = getpid();
			ppid = getppid();

			write(fd1[1], name, sizeof(name));
			write(fd1[1], &pid, sizeof(root));
			write(fd1[1], &ppid, sizeof(ppid));
			close(fd1[1]);

			//struct tree_node* node = malloc(sizeof(struct tree_node));

			node->left = NULL;
			node->right = NULL;

			while((current->left) != NULL){
				current = current->left;
			}

			current->left = node;

			node->nodeName = strdup(ptr->nodeNameLeft);

			close(fd1[0]);
			//write(fd1[1], *node, sizeof(node));
			close(fd1[1]);

			return createTree(ptr->next);

			exit(1);			
		}else {

			close(fd1[1]);
			read(fd1[0], name, sizeof(name));
			read(fd1[0], &pid, sizeof(root));
			read(fd1[0], &ppid, sizeof(ppid));
			//read(fd1[0], *node, sizeof(node));
			close(fd1[0]);

			// ptr->next->left->nodeName = strdup(name);
			// ptr->next->pid = pid;
			// ptr->next->ppid = ppid;

			while((wpid2 = wait(&status2)) > 0);
		}

		int pid1;
		int ppid1;
		char* name2;

		int fd2[2];
		pipe(fd2);

		pid_t pid3 = fork();
		pid_t wpid3;
		int status3 = 0;
		if(pid3 == 0){
			sleep(1);

			//printf("Second fork in child ==2\n");

			printf("Node %s: Pid: %d, ParentPid: %d\n", ptr->nodeNameRight, getpid(), getppid());
			
			close(fd2[0]);

			// name2 = ptr->nodeNameRight;			
			// pid1 = getpid();
			// ppid1 = getppid();

			write(fd2[1], name2, sizeof(name2));
			write(fd2[1], &pid1, sizeof(pid1));
			write(fd2[1], &ppid1, sizeof(ppid1));
			close(fd2[1]);

			struct tree_node* node1 = malloc(sizeof(struct tree_node));
			node1->left = NULL;
			node1->right = NULL;

			while((current->right) != NULL){
				current = current->right;
			}

			current->right = node1;
			current->nodeName = strdup(ptr->nodeNameRight);

			if(strcmp(root->nodeNameRight, ptr->nodeNameRight) == 0){
				return;
			}			

			return createTree(ptr->next);

			exit(1);			
		}else{

			close(fd2[1]);

			read(fd2[0], name2, sizeof(name2));
			read(fd2[0], &pid1, sizeof(pid1));
			read(fd2[0], &ppid1, sizeof(ppid1));
			close(fd2[0]);

			// ptr->next->right->nodeName = strdup(name2);
			// ptr->next->pid = pid1;
			// ptr->next->ppid = ppid1;

			while((wpid3 = wait(&status3)) > 0);
		}
		
	}

	if(strcmp(ptr->children_no,"1") == 0){

		int pid;
		int ppid;

		int fd1[2];
		pipe(fd1);

		pid_t pid1 = fork();
		pid_t wpid1;
		int status1 = 0;
		if(pid1 == 0){

			//printf("fork in child ==1\n");

			printf("Node %s: Pid: %d, ParentPid: %d\n", ptr->nodeNameLeft, getpid(), getppid());

			close(fd1[0]);
			pid = getpid();
			ppid = getppid();

			write(fd1[1], &pid, sizeof(pid));
			write(fd1[1], &ppid, sizeof(ppid));
			close(fd1[1]);

			struct tree_node* node = malloc(sizeof(struct tree_node));
			node->left = NULL;
			node->right = NULL;
	
			while((current->left) != NULL){
				current = current->left;
			}			

			current->left = node;
			current->nodeName = strdup(ptr->nodeNameLeft);

			return createTree(ptr->next);

			exit(1);

		}else if(pid1 > 0){

			close(fd1[1]);
			read(fd1[0], &pid, sizeof(pid));
			read(fd1[0], &ppid, sizeof(ppid));
			close(fd1[0]);

			ptr->next->pid = pid;
			ptr->next->ppid = ppid;

			while((wpid1 = wait(&status1)) > 0);

		}
	}




}

void read_tree_file(const char* filename){

	FILE* file = fopen(filename,"r");

	root = malloc(sizeof(struct tree_node));
	struct tree_node* current = malloc(sizeof(struct tree_node));

	char buffer[10];
	fgets(buffer, 10, file);

	char* token = strtok(buffer, " ");
	root->nodeName = strdup(token);

	token = strtok(NULL, " ");
	root->children_no = strdup(token);

	token = strtok(NULL, " ");
	root->nodeNameLeft = strdup(token);

	token = strtok(NULL, "\r");
	root->nodeNameRight = strdup(token);

	//root->left = NULL;
	//root->right = NULL;

	current = root;
	

	while(fgets(buffer, 10, file)){
		if(current != NULL){
			while(current->next != NULL){
				current = current->next;
			}
		}

		current->next = malloc(sizeof(struct tree_node));
		current = current->next;

		char *token = strtok(buffer, " ");
		current->nodeName = strdup(token);

		token = strtok(NULL, " ");
		current->children_no = strdup(token);

		if(strcmp(current->children_no, "2") == 0){
			token = strtok(NULL, " ");
			current->nodeNameLeft = strdup(token);

			token = strtok(NULL, "\r");
			current->nodeNameRight = strdup(token);

		}else if(strcmp(current->children_no, "1") == 0){
			token = strtok(NULL, "\r");
			current->nodeNameLeft = strdup(token);

		}else if(strcmp(current->children_no, "0\r\n") == 0){
			current->children_no = strdup("0");
		}

		// token = strtok(NULL, "\r");

		current->next = NULL;

	}

	current = root;

	//createTree(root);
	fclose(file);
	return;
	//createTree()

}

void print_tree(struct tree_node* root){

	if(root == NULL){
		return;
	}

	printf("Node: %s, pid: %d, ppid: %d\n", root->nodeName, root->pid, root->ppid);
	print_tree(root->left);
	print_tree(root->right);

}

int main(){

	
	fflush(stdout);

	read_tree_file("Input_Problem2.txt");

	printf("Root: %s: Pid: %d\n", root->nodeName, getpid());

	root->pid = getpid();
	createTree(root);

	fflush(stdout);

	return 0;
}