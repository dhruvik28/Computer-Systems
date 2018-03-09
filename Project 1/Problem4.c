#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct tree_node{
    struct tree_node* left;
    struct tree_node* right;
    char* operand;
    int integerLeft;
    int integerRight;
};

struct linkedList{
	char* line;

	struct linkedList* next;
};

//void createTree(struct tree_node* ptr);
void read_tree_file(const char* filename);
//void print_tree(struct tree_node* root);
int calculate_tree(struct linkedList* head);

struct tree_node *ptr = NULL;
struct linkedList *head = NULL;

// void createTree(struct tree_node* ptr){

// 	struct tree_node *current = malloc(sizeof(struct tree_node));
// 	//ptr = malloc(sizeof(struct tree_node));


// 	current = root;

// 	if(strcmp(ptr->children_no, "2") == 0){

// 		pid_t pid2 = fork();
// 		pid_t wpid2;
// 		int status2 = 0;

// 		if(pid2 == 0){		

// 			printf("Node %s: Pid: %d, ParentPid: %d\n", ptr->nodeNameLeft, getpid(), getppid());


// 			struct tree_node* node = malloc(sizeof(struct tree_node));

// 			node->left = NULL;
// 			node->right = NULL;

// 			while((current->left) != NULL){
// 				current = current->left;
// 			}

// 			current->left = node;

// 			node->nodeName = strdup(ptr->nodeNameLeft);

// 			return createTree(ptr->next);

// 		}else {

// 			while((wpid2 = wait(&status2)) > 0);
// 		}

// 		pid_t pid3 = fork();
// 		pid_t wpid3;
// 		int status3 = 0;
// 		if(pid3 == 0){

// 			printf("Node %s: Pid: %d, ParentPid: %d\n", ptr->nodeNameRight, getpid(), getppid());

// 			struct tree_node* node1 = malloc(sizeof(struct tree_node));
// 			node1->left = NULL;
// 			node1->right = NULL;

// 			while((current->right) != NULL){
// 				current = current->right;
// 			}

// 			current->right = node1;
// 			current->nodeName = strdup(ptr->nodeNameRight);

// 			if(strcmp(root->nodeNameRight, ptr->nodeNameRight) == 0){
// 				return;
// 			}			

// 			return createTree(ptr->next);

// 		}else{
// 			while((wpid3 = wait(&status3)) > 0);
// 		}
		
// 	}

// 	if(strcmp(ptr->children_no,"1") == 0){

// 		pid_t pid1 = fork();
// 		pid_t wpid1;
// 		int status1 = 0;
// 		if(pid1 == 0){

// 			printf("Node %s: Pid: %d, ParentPid: %d\n", ptr->nodeNameLeft, getpid(), getppid());

// 			struct tree_node* node = malloc(sizeof(struct tree_node));
// 			node->left = NULL;
// 			node->right = NULL;
	
// 			while((current->left) != NULL){
// 				current = current->left;
// 			}			

// 			current->left = node;
// 			current->nodeName = strdup(ptr->nodeNameLeft);

// 			return createTree(ptr->next);

// 		}else if(pid1 > 0){

// 			while((wpid1 = wait(&status1)) > 0);
// 		}
// 	}
// }

void read_tree_file(const char* filename){

	FILE* file = fopen(filename,"r");

	//root = malloc(sizeof(struct tree_node));
	// struct tree_node* current = malloc(sizeof(struct tree_node));

	struct linkedList* current = malloc(sizeof(struct linkedList));

	head = malloc(sizeof(struct linkedList));

	char buffer[10];
	fgets(buffer, 10, file);

	char* token = strtok(buffer, "\r");
	head->line = strdup(token);

	// token = strtok(NULL, " ");
	// if(strcmp(token, "*") == 0 || strcmp(token, "+") == 0){
	// 	root->right->operand = strdup(token);
	// }else{
	// 	root->left->integerLeft = atoi(token);
	// }

	// token = strtok(NULL, "\r");
	// root->right->integerRight = atoi(token);

	current = head;
	
	while(fgets(buffer, 10, file)){

		if(current != NULL){
			while(current->next != NULL){
				current = current->next;
			}
		}

		current->next = malloc(sizeof(struct tree_node));
		// current->right = malloc(sizeof(struct tree_node));
		// current->left = malloc(sizeof(struct tree_node));
		current = current->next;

		char *token = strtok(buffer, "\r");
		current->line = strdup(token);

		// token = strtok(NULL, " ");
		// if(strcmp(token, "*") == 0 || strcmp(token, "+") == 0){
		// 	current->operand = strdup(token);
		// }else{
		// 	current->integerLeft = atoi(token);
		// }

		// token = strtok(NULL, "\r");
		// current->integerRight = atoi(token);

	}

	current = head;

	//createTree(root);
	fclose(file);
	return;

}

int calculate_tree(struct linkedList *head){

	struct tree_node* ptr = malloc(sizeof(struct tree_node));

	//ptr->right = malloc(sizeof(struct tree_node));
	//ptr->left = malloc(sizeof(struct tree_node));

	char* buffer = strdup(head->line);

	char* token = strtok(buffer, " ");
	ptr->operand = strdup(token);

	int fd1[2];
	int left;
	int right;

	int fd2[2];
	int fd3[2];
	int fd4[2];
	int fd5[2];
	int fd6[2];

	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);
	pipe(fd5);
	pipe(fd6);

	pid_t pid = fork();
	pid_t wpid;
	int status = 0;

	if(pid == 0){

		close(fd1[0]);
		close(fd2[0]);
		close(fd3[0]);
		close(fd4[0]);
		close(fd5[0]);
		close(fd6[0]);


		if(ptr == NULL){
			return 0;
		}	

		token = strtok(NULL, " ");
		if(strcmp(token, "*") == 0 || strcmp(token, "+") == 0){
			ptr->right->operand = strdup(token);
			token = strtok(NULL, "\r");
			ptr->left->integerLeft = atoi(token);

			write(fd1[1], ptr->right->operand, sizeof(ptr->right->operand));
			close(fd1[1]);

			write(fd2[1], &ptr->left->integerLeft, sizeof(ptr->left->integerLeft));
			close(fd2[1]);

			ptr = ptr->right;
			return calculate_tree(head->next);
			exit(1);
		}else{
			int left = atoi(token);
			token = strtok(NULL, "\r");
			int right = atoi(token);

			if(strcmp(ptr->operand, "*") == 0){

				ptr->left->integerLeft = left;
				ptr->right->integerRight = right;

				write(fd3[1], &ptr->left->integerLeft, sizeof(ptr->left->integerLeft));
				close(fd3[1]);

				write(fd4[1], &ptr->right->integerRight, sizeof(ptr->right->integerRight));
				close(fd4[1]);

				return (left*right);
				exit(1);
			}

			if(strcmp(ptr->operand, "+") == 0){

				ptr->left->integerLeft = left;
				ptr->right->integerRight = right;

				write(fd5[1], &ptr->left->integerLeft, sizeof(ptr->left->integerLeft));
				close(fd5[1]);

				write(fd6[1], &ptr->right->integerRight, sizeof(ptr->right->integerRight));
				close(fd6[1]);

				return (left + right);
				exit(1);
			}
		}

	}else{
		while((wpid = wait(&status)) > 0);

		close(fd1[1]);
		read(fd1[0], ptr->right->operand, sizeof(ptr->right->operand));

		close(fd2[1]);
		read(fd2[0], &ptr->left->integerLeft, sizeof(ptr->left->integerLeft));

		close(fd3[1]);
		read(fd3[0], &ptr->left->integerLeft, sizeof(ptr->left->integerLeft));

		close(fd4[1]);
		read(fd4[0], &ptr->right->integerRight, sizeof(ptr->right->integerRight));

		close(fd5[1]);
		read(fd5[0], &ptr->left->integerLeft, sizeof(ptr->left->integerLeft));

		close(fd6[1]);
		read(fd6[0], &ptr->right->integerRight, sizeof(ptr->right->integerRight));

		close(fd1[0]);
		close(fd2[0]);
		close(fd3[0]);
		close(fd4[0]);
		close(fd5[0]);
		close(fd6[0]);
	


	}


}

// void print_tree(struct tree_node* root){

// 	if(root == NULL){
// 		return;
// 	}

// 	printf("Node: %s, pid: %d, ppid: %d\n", root->nodeName, root->pid, root->ppid);
// 	print_tree(root->left);
// 	print_tree(root->right);

// }

int main(){

	fflush(stdout);

	read_tree_file("Input_Problem4.txt");

	//ptr = malloc(sizeof(struct tree_node));

	//createTree(root);

	int result = calculate_tree(head);

	//printf("%d\n", result);

	return 0;
}