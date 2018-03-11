#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

struct tree_node{
    struct tree_node* right;
    char* operand;
    int integerLeft;
    int integerRight;
    int result;

    int pid;
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

int root;


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

	ptr = malloc(sizeof(struct tree_node));

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
	int fd7[2];
	int fd8[2];

	pipe(fd1);
	pipe(fd2);
	pipe(fd3);
	pipe(fd4);
	pipe(fd5);
	pipe(fd6);
	pipe(fd7);
	pipe(fd8);

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
		close(fd7[0]);
		close(fd8[0]);


		if(ptr == NULL){
			return 0;
		}	

		token = strtok(NULL, " ");
		if(strcmp(token, "*") == 0 || strcmp(token, "+") == 0){
			ptr->right->operand = strdup(token);
			token = strtok(NULL, "\r");
			ptr->integerLeft = atoi(token);

			write(fd1[1], ptr->right->operand, sizeof(ptr->right->operand));
			close(fd1[1]);

			write(fd2[1], &ptr->integerLeft, sizeof(ptr->integerLeft));
			close(fd2[1]);

			ptr = ptr->right;
			return calculate_tree(head->next);
			exit(1);
		}else{
			int left = atoi(token);
			token = strtok(NULL, "\r");
			int right = atoi(token);

			if(strcmp(ptr->operand, "*") == 0){

				ptr->integerLeft = left;
				ptr->integerRight = right;
				ptr->result = left*right;
			printf("Result: %d\n", ptr->result);


				write(fd3[1], &ptr->integerLeft, sizeof(ptr->integerLeft));
				close(fd3[1]);

				write(fd4[1], &ptr->integerRight, sizeof(ptr->integerRight));
				close(fd4[1]);

				write(fd7[1], &ptr->result, sizeof(ptr->result));
				close(fd7[1]);

				ptr->pid = getpid();




				//return (left*right);
				exit(1);
			}

			if(strcmp(ptr->operand, "+") == 0){

				ptr->integerLeft = left;
				ptr->integerRight = right;

				ptr->result = left+right;
				printf("Result: %d\n", ptr->result);


				write(fd5[1], &ptr->integerLeft, sizeof(ptr->integerLeft));
				close(fd5[1]);

				write(fd6[1], &ptr->integerRight, sizeof(ptr->integerRight));
				close(fd6[1]);

				write(fd8[1], &ptr->result, sizeof(ptr->result));
				close(fd8[1]);


				//return (left + right);
				exit(1);
			}
		}

	}else if(pid > 0){
		while((wpid = wait(&status)) > 0);

		close(fd1[1]);
		read(fd1[0], ptr->right->operand, sizeof(ptr->right->operand));

		close(fd2[1]);
		read(fd2[0], &ptr->integerLeft, sizeof(ptr->integerLeft));

		close(fd3[1]);
		read(fd3[0], &ptr->integerLeft, sizeof(ptr->integerLeft));

		close(fd4[1]);
		read(fd4[0], &ptr->integerRight, sizeof(ptr->integerRight));

		close(fd5[1]);
		read(fd5[0], &ptr->integerLeft, sizeof(ptr->integerLeft));

		close(fd6[1]);
		read(fd6[0], &ptr->integerRight, sizeof(ptr->integerRight));

		close(fd7[1]);
		read(fd7[0], &ptr->result, sizeof(ptr->result));
		close(fd7[0]);

		close(fd8[1]);
		read(fd8[0], &ptr->result, sizeof(ptr->result));
		close(fd8[0]);

		close(fd1[0]);
		close(fd2[0]);
		close(fd3[0]);
		close(fd4[0]);
		close(fd5[0]);
		close(fd6[0]);
	}


	//printf("Result: %d\n", ptr->result);

	// int fd0[2];
	// pipe(fd0);

	// if(root == getppid()){
	// 	// printf("in main1: %s\n", ptr->operand);
	// 	// printf("in main2: %d\n", ptr->integerLeft);
	// 	// printf("in main3: %d\n", ptr->integerRight);
	// 	// printf("in main4: %d\n", ptr->result);

	// 	if(strcmp(ptr->operand, "+") == 0){
	// 		ptr->result = ptr->integerRight + ptr->integerLeft;
	// 		printf("Result: %d\n", ptr->result);

			

	// 		close(fd0[0]);
	// 		write(fd0[1], &ptr->result, sizeof(ptr->result));
	// 		close(fd0[1]);

	// 		return calculate_tree(head);

	// 		exit(1);
	// 	}
	// }

	// printf("def out: %d\n", ptr->result);


	// 	close(fd0[1]);
	// 	read(fd0[0], &ptr->result, sizeof(ptr->result));
	// 	close(fd0[0]);

	// printf("def out: %d\n", ptr->result);

	// if(root == getpid()){
	// 	// printf("outside1: %s\n", ptr->operand);
	// 	// printf("outside2: %d\n", ptr->integerLeft);
	// 	// printf("outside3: %d\n", ptr->integerRight);
	// 	// printf("outside4: %d\n", ptr->result);

	// 	printf("comes here: %d\n", ptr->result);

	// 	printf("also comes here: %d\n", ptr->integerLeft);
	

	// 	//printf("outside41: %d\n", ptr->right->result);

	// }

	// // while(root != getpid()){
	// // 	if(strcmp(ptr->operand, "*") == 0){
	// // 		int answer = ptr->integerLeft*ptr->result;

	// // 	}	
	// // }





}


int main(){

	fflush(stdout);

	read_tree_file("Input_Problem4.txt");

	//ptr = malloc(sizeof(struct tree_node));

	//createTree(root);

	root = getpid();

	int result = calculate_tree(head);

	// printf("%d\n", result);

	int fd10[2];
	pipe(fd10);

	pid_t wpid;
	int status;

	if(root != getpid()){

		close(fd10[0]);
		write(fd10[1], &ptr->result, sizeof(ptr->result));
		close(fd10[1]);

	}

	if(root == getpid()){
		while((wpid = wait(&status)) > 0);
	}

	close(fd10[1]);
	read(fd10[0], &ptr->result, sizeof(ptr->result));
	close(fd10[0]);


	return;


	// if(root != getpid()){
	// 	printf("in main1: %s\n", ptr->operand);
	// 	printf("in main2: %d\n", ptr->integerLeft);
	// 	printf("in main3: %d\n", ptr->integerRight);
	// 	printf("in main4: %d\n", ptr->result);

	// 	if(strcmp(ptr->operand, "+") == 0){
	// 		ptr->result = ptr->integerRight + ptr->integerLeft;

	// 		printf("if +: %d\n", ptr->result);
	// 	}
	// 	exit(1);
	// }


	// printf("in main7: %s\n", ptr->operand);

	// printf("in main8: %s\n", ptr->right->operand);

	// printf("in main9: %d\n", ptr->right->integerRight);


	



	//printf("%d\n", result);
}