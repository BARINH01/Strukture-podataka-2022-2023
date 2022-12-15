#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX_STRING 256



typedef struct _directory {
	char name[MAX_STRING];
	struct _directory *child;
	struct _directory *sibling;
}directory;


typedef struct _stack {
	directory *parent;
	struct _stack *next;
}stack;

directory *md(directory *current, directory *element);
int dir(directory *q);
stack *create_stack();
directory *create_directory();
int free_all(directory *parent);
directory *cd_dir(stack *st,directory *current);
int push(stack *st,directory *current);
directory *pop(stack *stack_1);
int print_path(stack *input_stack);


int main(){
    
	char input[MAX_STRING]="0";

	stack *stack_1 = NULL;
	directory *C = NULL, *current = NULL, *element = NULL;

	stack_1 = create_stack();
	C = create_directory();
	current = C;

	while (strcmp(input,"exit")!=0){

		scanf(" %[^\n]", input);
		
		if(strcmp(input,"md")==0){
		    
			element = create_directory();
			current->child = md(current->child, element);		    
		}


		else if(strcmp(input,"cd dir")==0){
		 	element = cd_dir(stack_1, current);
			current = element;   
		}

        else if(strcmp(input,"cd")==0){
         	
         	element = pop(stack_1);
			if (!element)
				printf("There are no parent directories to move directory\n");
			else
				current = element;   
        }


		else if(strcmp(input,"dir")==0){
		    
		  	dir(current);  
		}

		else{
		printf("WRONG INPUT!\nTRY AGAIN: \n");
		}
		
		print_path(stack_1);
		
	}
	
	free_all(C);
	return EXIT_SUCCESS;
}


stack *create_stack(){
    
	stack *newElement = NULL;
	newElement = malloc(sizeof(stack));
	
	if (newElement == NULL){
		perror("Can't allocate memory!\n");
		return NULL;
	}
	newElement->next = NULL;

	return newElement;
}

directory *create_directory(){
    
	directory *newElement = NULL;
	newElement = malloc(sizeof(directory));
	
	if (newElement == NULL){
	    
		perror("Can't allocate memory!\n");
		return NULL;
	}
	
	newElement->child = NULL;
	newElement->sibling = NULL;

	printf("\nEnter directory name: ");
	scanf(" %[^\n]", newElement->name);

	return newElement;
}


directory *md(directory *current,directory *element){
    
	if (current == NULL){
	    return element;
	}
		
	if (strcmp(current->name, element->name) < 0){
		current->sibling = md(current->sibling, element);
	}
	
	else if (strcmp(current->name, element->name) > 0){
		element->sibling = current;
		return element;
	}
	
	else if (strcmp(current->name, element->name) == 0){
		printf("\nThat name already exist!");
	}
	return current;
}

int dir(directory *current){
    
	directory *temp = NULL;
	printf("%s: \n", current->name);

	if (current->child != NULL)
	{
		temp = current->child;
		while (temp != NULL)
		{
			printf("\t%s\t", temp->name);
			temp = temp->sibling;
		}
	}
	printf("\n");
	return EXIT_SUCCESS;
}

int free_all(directory *parent){
    
	if (parent == NULL)
		return EXIT_SUCCESS;
		
	free_all(parent->sibling);
	free_all(parent->child);
	return EXIT_SUCCESS;
}

directory *cd_dir(stack *st, directory *current){
    
	directory *for_delete = NULL;
	directory *temp = NULL;
	char  name[MAX_STRING] = { 0 };

	printf("Enter directory name you want to select \n");
	scanf(" %s", name);

	if (current->child == NULL){
		printf("Directory is empty!\n");
		return NULL;
	}
	
	temp = current->child;
	
	while (temp != NULL){
		if (strcmp(temp->name, name) == 0)
			for_delete = temp;
		temp = temp->sibling;
	}
	
	push(st, current);
	return for_delete;
}

int push(stack *st,directory *current){
	
	stack *q = NULL;
	q = create_stack();
	q->parent = current;
	q->next = st->next;
	st->next = q;
	return 0;
}

directory *pop(stack *stack_1){
    
	stack *temp_s = NULL;
	directory *q = NULL;

    temp_s=malloc(sizeof(stack));

	if (stack_1 == NULL || stack_1->next == NULL){
	  	
	  	return NULL;  
	}

	temp_s = stack_1->next;
	q = temp_s->parent;
	stack_1->next = temp_s->next;

	free(temp_s);
	return q;
}

int print_path(stack *input_stack){
    directory *temp=input_stack->parent;
    if(input_stack->next==NULL){
        printf("%s",temp->name);
        printf("/");
        return 0;
    }
    print_path(input_stack->next);
    printf("%s",temp->name);

    return 0;
}


