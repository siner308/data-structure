#include <stdio.h>
#include <malloc.h>

#define CREATE_NEW_NODE (node*)malloc(sizeof(node))

typedef struct Node node;
struct Node{
	int num;
	node *next;
};

int emptyTowerCheck(node**);
node *makeTower(node*, int);
node *pushStack(node*, int);
int findTower(node**);
void moveTower(node**, int, int, int);
void moveOnePiece(node**, int, int);
void deleteTower(node**);
node *freeStack(node*);
void printTower(node**);
node *printOneTower(node*, int);

int main(void){
	node *front[3] = { 0, 0, 0 };
	int nMenu = 0;
	int nHeight_Total = 0;
	int temp = 0;
	int nBefore = 0, nAfter = 0;
	int isEmpty = 0;

	while (nMenu != 5){
		printf("1.Make 2.Move 3.Delete 4.Print 5.Exit : ");
		scanf("%d", &nMenu);

		isEmpty = emptyTowerCheck(front);

		switch (nMenu)
		{
		case 1:
			// empty tower
			if (isEmpty){
				printf("enter height : ");
				scanf("%d", &temp);
				nHeight_Total = temp;

				front[0] = makeTower(front[0], nHeight_Total);

			}
			else{
				printf("there are towers already\n");
			}

			break;

		case 2:
			// empty tower
			if (isEmpty){
				printf("empty tower\n");
			}

			// not empty tower
			else{
				nBefore = findTower(front);
				printf("where to go? (now : %d)", nBefore);
				scanf("%d", &nAfter);

				// right target
				if ((nBefore != nAfter) && ((nAfter < 3) && (nAfter >= 0))){
					moveTower(front, nHeight_Total, nBefore, nAfter);
				}

				// wrong target
				else{
					printf("wrong location\n");
				}
			}

			break;

		case 3:
			// empty tower
			if (isEmpty){
				printf("empty tower\n");
			}

			// not empty tower
			else{
				deleteTower(front);
			}

			break;

		case 4:
			// empty tower
			if (isEmpty){
				printf("empty tower\n");
			}

			// not empty tower
			else{
				printTower(front);
			}

			break;

		default:
			break;
		}
	}

	// exit
	deleteTower(front);

	return 0;
} // end of main

int emptyTowerCheck(node **front){
	// empty tower
	if ((front[0] == NULL) && (front[1] == NULL) && (front[2] == NULL)){
		return 1;
	}

	// not empty tower
	else{
		return 0;
	}
}

node *makeTower(node *front, int nHeight_Total){
	int i = 0;

	// set tower
	for (i = nHeight_Total; i > 0; i--){
		front = pushStack(front, i);
	}

	return front;
} // end of makeTower

node *pushStack(node *front, int i){
	node *temp;

	// empty tower
	if (front == NULL){
		front = CREATE_NEW_NODE;
		front->next = NULL;
		front->num = i;
	}

	// not empty tower
	else{
		temp = CREATE_NEW_NODE;
		temp->next = front;
		temp->num = i;
		front = temp;
	}

	return front;
} // end of pushStack

node *popStack(node *front){
	node *temp;

	temp = front;
	front = front->next;

	free(temp);

	return front;
} // end of popStack

int findTower(node *front[3]){
	// NULL check
	if (front[0] != NULL){
		return 0;
	}

	else if (front[1] != NULL){
		return 1;
	}

	else if (front[2] != NULL){
		return 2;
	}
} // end of findTower

void moveTower(node **front, int nHeight_Total, int before, int after){
	// escape condition
	if (nHeight_Total == 1){
		moveOnePiece(front, before, after);
	}

	// recursion
	else{
		moveTower(front, nHeight_Total - 1, before, 3 - (after + before));
		moveOnePiece(front, before, after);
		moveTower(front, nHeight_Total - 1, 3 - (after + before), after);
	}
} // end of moveTower

void moveOnePiece(node **front, int before, int after){
	int num = 0;
	node *temp;

	// get value before pop
	num = front[before]->num;

	// pop & stack
	front[before] = popStack(front[before]);
	front[after] = pushStack(front[after], num);

	// print for check
	printTower(front);
} // end of moveOnePiece

void deleteTower(node *front[3]){
	int i = 0;

	// free each towers
	for (i = 0; i < 3; i++){
		front[i] = freeStack(front[i]);
	}
} // end of deleteTower

node *freeStack(node *front){
	node *temp;

	// free tower
	while (front != NULL){
		temp = front;
		front = front->next;
		free(temp);
		temp = 0;
	}

	return front;
} // end of freeStack

void printTower(node *front[3]){
	int i = 0, j = 0;
	int top = 0;
	int cnt = 0;
	int nHeight_Total = 0;
	node *temp[3];
	int nHeight_Single[3] = { 0, 0, 0 };

	// copy tower & get height
	for (i = 0; i < 3; i++){
		temp[i] = front[i]; // set temp

		// while check whole tower
		while (temp[i] != NULL){

			// set nHeight_Total
			if (temp[i]->num > nHeight_Total){
				nHeight_Total = temp[i]->num;
			}

			// set nHeight_Single
			temp[i] = temp[i]->next;
			nHeight_Single[i]++;

		}

		temp[i] = front[i]; // reset temp for use below
	}

	// set highest height
	for (i = 0; i < 3; i++){
		if (nHeight_Single[i] > top){
			top = nHeight_Single[i];
		}
	}

	printf("\n");

	// while not empty tower
	while (nHeight_Single[0] != 0 || nHeight_Single[1] != 0 || nHeight_Single[2] != 0){

		// print each tower
		for (i = 0; i < 3; i++){

			// there is block to print -> print block
			if (nHeight_Single[i] == top){
				temp[i] = printOneTower(temp[i], nHeight_Total);
				nHeight_Single[i]--;
			}

			// there is no block to print -> print blank
			else{
				for (j = 0; j < nHeight_Total; j++){
					printf("  ");
				}
			}

			printf("\t");
		}

		top--;
		printf("\n");
	}

	printf("\n");
} // end of printTower

node *printOneTower(node *temp, int nHeight_Total){
	int i = 0;

	for (i = 0; i < nHeight_Total - temp->num; i++){
		printf(" "); // print blank
	}

	for (i = 0; i < temp->num; i++){
		printf("=="); // print block
	}

	for (i = 0; i < nHeight_Total - temp->num; i++){
		printf(" "); // print blank
	}

	temp = temp->next;
}