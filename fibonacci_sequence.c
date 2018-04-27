#include <stdio.h>
#include <malloc.h>

#define CREATE_NEW_NODE (node*)malloc(sizeof(node))

typedef struct Node node;
struct Node{
	int num;
	int cnt;
	node *prev;
	node *next;
};

node *initFibonacci(node*, int, int);
node *fibonacci(node*, int);
node *initQ(node*, int);
node *putQ(node*, int);
node *getQ(node*);
int sumFibonacci(node*);
node *freeQ(node*);

int main(void){
	int nMenu = 0;
	int cnt = 0;
	node *front = 0;

	while (nMenu != 3){
		printf("1.fibonacci 2.Delete 3.Exit : ");
		scanf("%d", &nMenu);

		switch (nMenu)
		{
		case 1:		// fibonacci
			printf("enter fibonacci count : ");
			scanf("%d", &cnt);

			// empty queue -> init
			if (front == NULL){
				front = initFibonacci(front, 1, 1); // init value (1, 1)
				cnt -= 2;
			}

			// not empty queue -> continue
			front = fibonacci(front, cnt);
			break;

		case 2:		// delete
			front = freeQ(front);
			break;

		default:
			break;
		}
	}

	freeQ(front);

	return 0;
}

node *initFibonacci(node *front, int num1, int num2){
	front = putQ(front, num1);
	front = putQ(front, num2);

	printf("  %d\n  %d\n", num1, num2);

	return front;
}

node *putQ(node *front, int addnum){
	node *temp;

	// empty queue
	if (front == NULL){
		front = CREATE_NEW_NODE;

		front->num = addnum;
		front->next = NULL;
		front->prev = NULL;
	}

	// not empty queue
	else{
		temp = CREATE_NEW_NODE;

		temp->num = addnum;
		temp->next = front;
		temp->prev = NULL;

		front->prev = temp;
		front = front->prev;
	}

	return front;
}

node *fibonacci(node *front, int cnt){
	int sum = 0;
	node *temp;

	while (cnt > 0){
		sum = sumFibonacci(front); // calc sum

		// get & put
		front = getQ(front);
		front = putQ(front, sum);
		
		printf("  %d\n", sum); // print
		cnt--; // check count
	}
	printf("\n");

	return front;
}

int sumFibonacci(node *front){
	node *temp;
	int sum = 0;
	temp = front;

	// add num
	while (temp != NULL){
		sum += temp->num;
		temp = temp->next;
	}

	return sum;
}

node *getQ(node *front){
	node *temp;
	node *temp_rear;

	temp_rear = front;

	// if front != rear
	if (temp_rear->next != NULL){

		// while find rear
		while (temp_rear->next != NULL){
			temp_rear = temp_rear->next;
		}

		// set temp
		temp = temp_rear;
		temp_rear = temp_rear->prev;
		temp_rear->next = NULL;
	}

	// front == rear
	else{
		// set temp
		temp = temp_rear;
	
		front = 0;
		printf("empty queue now\n");
	}

	free(temp);

	return front;
}

node *freeQ(node *front){

	while (front != NULL){
		front = getQ(front);
	}

	return front;
}