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

   struct tree_node* next;
   char* line;
};

void createTree(struct tree_node* ptr);
void read_tree_file(const char* filename);

struct tree_node *root = NULL;

void createTree(struct tree_node* ptr){

	struct tree_node *current = malloc(sizeof(struct tree_node));
	//ptr = malloc(sizeof(struct tree_node));

	current = root;

	if(strcmp(ptr->children_no, "2") == 0){

		pid_t pid2 = fork();
		pid_t wpid2;
		int status2 = 0;

		if(pid2 == 0){				
			printf("Node %s: Child: %d, Parent: %d\n", ptr->nodeNameLeft, getpid(), getppid());
			struct tree_node* node = malloc(sizeof(struct tree_node));
			node->left = NULL;
			node->right = NULL;

			while((current->left) != NULL){
				current = current->left;
			}

			current->left = node;
			current->nodeName = strdup(ptr->nodeNameLeft);

			sleep(5);

			return createTree(ptr->next);

			exit(1);			
		}else {

			//while((wpid2 = wait(&status2)) > 0);
		}

		pid_t pid3 = fork();
		pid_t wpid3;
		int status3 = 0;
		if(pid3 == 0){
			sleep(1);

			printf("Node %s: Child: %d, Parent: %d\n", ptr->nodeNameRight, getpid(), getppid());
			struct tree_node* node1 = malloc(sizeof(struct tree_node));
			node1->left = NULL;
			node1->right = NULL;

			while((current->right) != NULL){
				current = current->right;
			}

			current->right = node1;
			current->nodeName = strdup(ptr->nodeNameRight);

			return createTree(ptr->next);

			exit(0);			
		}else{

			while((wpid3 = wait(&status3)) > 0);
		}
		
	}

	if(strcmp(ptr->children_no,"1") == 0){


		pid_t pid1 = fork();
		pid_t wpid1;
		int status1 = 0;
		if(pid1 == 0){

			printf("Node %s: Child: %d, Parent: %d\n", ptr->nodeNameLeft, getpid(), getppid());

			struct tree_node* node = malloc(sizeof(struct tree_node));
			node->left = NULL;
			node->right = NULL;
	
			while((current->left) != NULL){
				current = current->left;
			}			

			current->left = node;
			current->nodeName = strdup(ptr->nodeNameLeft);

			sleep(5);
			return createTree(ptr->next);

			exit(0);

		}else if(pid1 > 0){

			while((wpid1 = wait(&status1)) > 0);

		}
	}

	if(strcmp(current->children_no,"0") == 0){
		return;
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

		token = strtok(buffer, " ");
		current->nodeName = strdup(token);

		token = strtok(NULL, " ");
		current->children_no = strdup(token);

		if(strcmp(current->children_no, "2") == 0){
			token = strtok(NULL, "\r");
			current->line = strdup(token);
		}else if(strcmp(current->children_no, "1") == 0){
			token = strtok(NULL, "\r");
			current->nodeNameLeft = strdup(token);

			current->line = NULL;
		}else if(strcmp(current->children_no, "0") == 0){
			current->line = NULL;
		}

		// token = strtok(NULL, "\r");
		//current->line = strdup(token);
		current->next = NULL;
	}

	current = root;

	//createTree(root);
	fclose(file);
	return;
	//createTree()

}

int main(){

	//createTree('A', 2, 'B', 'C');
	//createTree('B', 1, 'D', '-');

	printf("Root: %d\n", getpid());
	fflush(stdout);

	read_tree_file("Input_Problem2.txt");

	createTree(root);

	// printf("%s\n", root->nodeNameLeft);
	// printf("%s\n", root->nodeNameRight);

	//createTree(root, "2", "B", "C");
	//createTree(root, 1, "D", "-");

	//sleep(3);
	//printf("%s\n", root->nodeNameLeft);

	//getchar();
	return;
}