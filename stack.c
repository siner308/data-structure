#include <stdio.h>
#include <malloc.h>

#define CREATE_NEW_NODE (node*)malloc(sizeof(node))

typedef struct Node node;
struct Node{
	int num;
	node *next;
};

node *initStack(node*, int);
node *pushStack(node*, int);
node *popStack(node*);
void printStack(node*);
void freeStack(node*);

int main(void){
	int addnum = 0;
	int nMenu = 0;
	node *front = 0;

	while (nMenu != 4){
		printf("1.Push 2.Pop 3.Print 4.Exit : ");
		scanf("%d", &nMenu);

		switch (nMenu)
		{
		case 1:
			printf("enter number : ");
			scanf("%d", &addnum);

			// empty stack
			if (front == NULL){
				front = initStack(front, addnum);
			}

			// not empty stack
			else{
				front = pushStack(front, addnum);
			}

			break;

		case 2:
			// empty stack
			if (front == NULL){
				printf("empty stack already\n");
			}

			// not empty stack
			else{
				front = popStack(front);
			}

			break;

		case 3:
			// empty stack
			if (front == NULL){
				printf("empty stack\n");
			}

			// not empty stack
			else{
				printStack(front);
			}
			
			break;

		default:
			break;
		}
	}

	freeStack(front);

	return 0;
}

node *initStack(node* front, int addnum){
	front = CREATE_NEW_NODE;

	front->next = NULL;
	front->num = addnum;
}

node *pushStack(node* front, int addnum){
	node *temp;
	temp = CREATE_NEW_NODE;

	temp->next = front;
	temp->num = addnum;

	front = temp;

	return front;
}

node *popStack(node* front){
	node *temp;

	temp = front;

	// front == rear
	if (front->next == NULL){
		front = 0;
		printf("empty stack now\n");
	}

	// front != rear
	else{
		front = front->next;
	}

	free(temp);

	return front;
}

void printStack(node* front){
	node *temp;
	temp = front;

	while (temp != NULL){
		printf("%d\n", temp->num);
		temp = temp->next;
	}
}

void freeStack(node* front){
	node *temp_front;
	node *temp;

	temp_front = front;

	while (temp_front != NULL){
		temp = temp_front;
		temp_front = temp_front->next;
		free(temp);
	}
}