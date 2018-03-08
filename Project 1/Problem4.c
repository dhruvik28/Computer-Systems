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
    char* nodeName;
};

int count;
struct tree_node *root = NULL; 

void makeTree(char * lines[])
{
	struct tree_node *current = malloc(sizeof(struct tree_node));
	current = root;  
	
	//get rid of newline characters
	for(int i = 0; i < count; i++)
	{
		lines[i] = strtok(lines[i] , "\n" );	
	}

	//parse contents of lines
	char* contents[count][3]; 
	for(int i = 0; i < count; i++)
	{
		contents[i][0] = strtok(lines[i] , " " );	
		contents[i][1] = strtok(NULL , " " );
		contents[i][2] = strtok(NULL , " " );
	}
	
	
	
	
	
	
}

void start(char* filename) 
{
	//get number of lines in file, stored in count
	count = 0;
	char temp_var;  
	FILE* file = fopen(filename,"r");
   	for (temp_var = getc(file); temp_var!= EOF; temp_var = getc(file))
        {
		if (temp_var == '\n') count++; 
	}
	fclose(file); 
	
 	//get contents of file, stored in lines
	char* lines[count];
	file = fopen(filename,"r"); 
	for(int i = 0; i < count; i++)
	{
		lines[i] = malloc(50); 
		fgets(lines[i], 15, file); 
	}
	fclose(file);
 	makeTree(lines); 
}

int main()
{
	start("Input_Problem4");
	
}
