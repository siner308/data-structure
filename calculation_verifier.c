#include <stdio.h>
#include <malloc.h>

#define CREATE_NEW_NODE (node*)malloc(sizeof(node))
#define BUF_MAX 1000

typedef struct Node node;
struct Node{
	char key;
	node *next;
};

node *push(node*, char);
char peek(node*);
int getLength(char*);
node *makeList(node*, char*); 
int isEmpty(node*);
int isOK(node*);
node *pop(node*);
node *popAllStack(node*);
void printStack(node*);


int main(void){
	node *front = 0;
	char strInput[BUF_MAX] = "";
	int lenInput = 0;
	int i = 0;

	// while strInput != '0'
	while (1){

		// enter strInput
		printf("enter expression (0 to quit)\n : ");
		gets(strInput);

		if (strInput[0] != '0'){

			// push all stack
			front = makeList(front, strInput);

			// empty check
			// not empty stack
			if (!isEmpty(front)){

				// expression check
				// OK
				if (isOK(front)){
					printf("OK\n");
				}

				// Not OK
				else{
					printf("NOT OK\n");
				}
			}

			// empty stack
			else{
				printf("stack is empty\n");
			}

			// pop all stack
			while (front != NULL){
				front = pop(front);
			}
		}

		else{
			break;
		}
	}

	return 0;
} // end of main

node* makeList(node *front, char *strInput){
	int i = 0;
	int lenInput = 0;
	lenInput = getLength(strInput);

	// make list
	for (i = lenInput; i > 0; i--){

		// if not blank, push
		if (strInput[i - 1] != ' '){
			front = push(front, strInput[i - 1]);
		}
	}


	return front;
} // end of makeList

int getLength(char *strInput){
	int i = 0;
	int lenInput = 0;

	// get length
	while (strInput[i] != '\0'){
		i++;
		lenInput++;
	}

	return lenInput;
} // end of getLength

node* push(node* front, char key){
	node *temp;
	
	// empty stack -> init
	if (front == NULL){
		front = CREATE_NEW_NODE;
		front->next = NULL;
		front->key = key;
	}

	// not empty stack -> push
	else{
		temp = CREATE_NEW_NODE;
		temp->next = front;
		temp->key = key;

		front = temp;
	}

	return front;
} // end of push

int isEmpty(node *front){
	// empty stack
	if (front == NULL){
		return 1;
	}

	// not empty stack
	else{
		return 0;
	}
} // end of isEmpty

int isOK(node *front){
	char key = 0;
	char key_next = 0;
	int bracket_big = 0;
	int bracket_mid = 0;
	int bracket_small = 0;
	node *temp;

	temp = front;

	while (temp != NULL){

		// set key
		key = peek(temp);
		if (temp->next != NULL){
			key_next = peek(temp->next);
		}


		// ok check
		// number : 0 ~ 9
		if ((key >= '0') && (key <= '9')){

			// next check
			if (temp->next != NULL){
				if ((key_next == '(') || (key_next == '{') || (key_next == '[')){
					return 0;
				}
			}
		}

		// operator : +, *, /
		else if ((key == '+') || (key == '/') || (key == '*')){

			// next check
			if (temp->next != NULL){
				if ((key_next == '+') || (key_next == '*') || (key_next == '/')){
					return 0;
				}
				else if ((key_next == ')') || (key_next == '}') || (key_next == ']')){
					return 0;
				}
			}
			else{
				return 0;
			}

		}

		// operator : -
		else if (key == '-'){

			// next check
			if (temp->next != NULL){
				if ((key_next == '+') || (key_next == '*') || (key_next == '/')){
					return 0;
				}
				else if (key_next == '-'){
					return 0;
				}
				else if ((key_next == ')') || (key_next == '}') || (key_next == ']')){
					return 0;
				}
			}
			else{
				return 0;
			}
		}

		// open bracket : (, {, [
		else if ((key == '(') || (key == '{') || (key == '[')){

			// next check
			if (temp->next != NULL){
				if ((key_next == '+') || (key_next == '*') || (key_next == '/')){
					return 0;
				}
				else if ((key_next == ')') || (key_next == '}') || (key_next == ']')){
					return 0;
				}
			}
			else{
				return 0;
			}

			// count bracket
			if (key == '('){
				bracket_small++;
			}
			else if (key == '{'){
				bracket_mid++;
			}
			else if (key == '['){
				bracket_big++;
			}
		}

		// close bracket : ), }, ]
		else if ((key == ')') || (key == '}') || (key == ']')){

			// next check
			if (temp->next != NULL){
				if ((key_next >= '0') && (key_next <= '9')){
					return 0;
				}
				else if ((key_next == '(') || (key_next == '{') || (key_next == '[')){
					return 0;
				}
			}

			// count bracket
			if (key == ')'){
				bracket_small--;
			}
			else if (key == '}'){
				bracket_mid--;
			}
			else if (key == ']'){
				bracket_big--;
			}
		}

		else{
			printf("wrong input\n");
		}

		// next stack
		temp = temp->next;
	}

	// bracket check
	if ((bracket_small == 0) && (bracket_mid == 0) && (bracket_big == 0)){
		return 1;
	}

	else{
		printf("bracket err (%d, %d, %d)\n",bracket_small, bracket_mid, bracket_big);
		return 0;
	}
} // end of isOK

node* pop(node* front){
	node *temp;
	temp = front;

	front = front->next;
	free(temp);

	return front;
} // end of pop

char peek(node* front){
	char key;
	key = front->key;

	return key;
} // end of peek


// for test
void printStack(node *front){
	node *temp;
	temp = front;

	while (temp != NULL){
		printf("%c ", temp->key);
		temp = temp->next;
	}
	printf("\n");
} // end of printStack