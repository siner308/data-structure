#include <stdio.h>
#include <malloc.h>

#define CREATE_NEW_NODE (node*)malloc(sizeof(node))

typedef struct Node node;
struct Node{
	int num;
	node *prev;
	node *next;
};

node *initQ(node*, int);
node *putQ(node*, int);
node *getQ(node*);
void printQ(node*);
void freeQ(node*);

int main(void){
	int nMenu = 0;
	int addnum = 0;
	node *front = 0;

	while (nMenu != 4){
		printf("1.Put 2.Get 3.Print 4.Exit : ");
		scanf("%d", &nMenu);
		
		switch (nMenu)
		{
		case 1:
			printf("enter number : ");
			scanf("%d", &addnum);

			// empty queue
			if (front == NULL){
				front = initQ(front, addnum);
			}

			// not empty queue
			else{
				front = putQ(front, addnum);
			}

			break;

		case 2:
			// empty queue
			if (front == NULL){
				printf("empty queue already\n");
			}

			// not empty queue
			else{
				front = getQ(front);
			}

			break;

		case 3:
			// empty queue
			if (front == NULL){
				printf("empty queue\n");
			}
			
			// not empty queue
			else{
				printQ(front);
			}
			
			break;

		default:
			break;
		}
	}

	freeQ(front);

	return 0;
}

node *initQ(node *front, int addnum){
	front = CREATE_NEW_NODE;

	front->next = NULL;
	front->prev = NULL;
	front->num = addnum;

	return front;
}

node *putQ(node *front, int addnum){
	node *temp;
	temp = CREATE_NEW_NODE;

	temp->num = addnum;
	temp->prev = NULL;
	temp->next = front;

	front->prev = temp;
	front = front->prev;

	return front;
}

node *getQ(node *front){
	node *temp;
	node *temp_rear;

	temp_rear = front;

	// if front == rear
	if (temp_rear->next != NULL){

		// while find rear
		while (temp_rear->next != NULL){
			temp_rear = temp_rear->next;
		}

		temp = temp_rear;	
		temp_rear = temp_rear->prev;
		temp_rear->next = NULL;
	}

	// front == rear
	else{
		temp = temp_rear;

		front = 0;
		printf("empty queue now\n");
	}

	free(temp);

	return front;
}

void printQ(node *front){
	node *temp;
	temp = front;

	while (temp != NULL){
		printf("%d\n", temp->num);
		temp = temp->next;
	}
}

void freeQ(node *front){
	node *temp_front;
	node *temp;

	temp_front = front;

	while (temp_front != NULL){
		temp = temp_front;
		temp_front = temp_front->next;
		free(temp);
	}
}