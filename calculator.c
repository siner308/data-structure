#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>

#define CREATE_NEW_NODE (node*)malloc(sizeof(node))
#define BUF_MAX 1000

typedef struct Node node;
struct Node{
	char key;
	int val;
	node *next;
};

int getLength(char*);
char *makePost(char*, int);
void calcPost(char*);
node *calcOperator(node*, char);
node *push(node*, char);
node *pop(node*);
//char peek(node*);
//int isEmpty(node*);
//void printStack(node*);


int main(void){
	char strInput[BUF_MAX] = ""; // infix
	char strPost[BUF_MAX] = "";  // postfix
	int lenInput = 0; // length of infix
	int result = 0; // answer of expression

	// while strInput != '0'
	while (strInput[0] != 'q'){
		// enter expression with infix
		printf("enter expression (q to quit)\n : ");
		gets(strInput);

		if (strInput[0] != 'q'){
			// get length
			lenInput = getLength(strInput);

			// make array with postfix
			strcpy(strPost, makePost(strInput, lenInput));
			// print for check
			printf("strPost = %s\n", strPost);

			// calculation
			calcPost(strPost);
		}
	}

	return 0;
} // end of main

int getLength(char *strInput){
	int i = 0;

	while (strInput[i] != '\0'){
		i++;
	}

	return i;
}

char *makePost(char *strInput, int lenInput){
	char *strPost;
	node *temp = 0;
	int i = 0, j = 0;

	// dynamic allocation
	strPost = (char*)malloc(sizeof(char)*BUF_MAX);

	// Infix -> Postfix
	for (i = 0; i < lenInput; i++){

		// number
		if ((strInput[i] >= '0') && (strInput[i] <= '9')){

			strPost[j] = strInput[i];
			j++;

			// if next array is not number (if this array is units)
			if (!((strInput[i + 1] >= '0') && (strInput[i + 1] <= '9'))){
				strPost[j] = ' ';
				j++;

				// not empty stack (for operator)
				if (temp != NULL){

					// pop stacks until reached 'open bracket')
					while (temp->key != '('){
						strPost[j] = temp->key;
						j++;
						strPost[j] = ' ';
						j++;

						temp = pop(temp);
						
						// if reached NULL, break.
						if (temp == NULL){
							break;
						}
					}
				}
			}
		}
		// plus, minus
		else if ((strInput[i] == '+') || (strInput[i] == '-')){
			temp = push(temp, strInput[i]);
		}

		// multiple, divide, mod
		else if ((strInput[i] == '*') || (strInput[i] == '/') || (strInput[i] == '%')){

			// 바로 이전에 덧셈, 뺄셈 연산자가 있었고, 괄호안에 있던게 아니라면, 
			// 그 연산자를 다시 스택으로 넣고, 그 위에 곱셈 연산자를 넣는다.
			if (((strPost[j - 2] == '+') || (strPost[j - 2] == '-')) && (strInput[i - 1] != ')')){
				temp = push(temp, strPost[j - 2]);
				j -= 2;
			}

			temp = push(temp, strInput[i]);
		}

		// open bracket
		else if (strInput[i] == '('){
			printf("open bracket\n");
			temp = push(temp, strInput[i]);
		}

		// close bracket
		else if (strInput[i] == ')'){
			printf("close bracket\n");

			// until reached 'open breacket', set to Postfix
			while (temp->key != '('){
				strPost[j] = temp->key;
				j++;
				strPost[j] = ' ';
				j++;

				temp = pop(temp);
			}
			temp = pop(temp);
		}

		// blank (pass this)
		else if (strInput[i] == ' '){

		}

		// error
		else{
			printf("wrong input\n");
		}
	}

	while (temp != NULL){
		if (temp->key != '('){

			strPost[j] = temp->key;
			j++;
			strPost[j] = ' ';
			j++;

			temp = pop(temp);
		}
		else{
			printf("bracket error\n");
		}
	}

	// last character is NULL
	strPost[j] = '\0';

	return strPost;
}

void calcPost(char *strPost){
	int i = 0;
	int retVal = 0;
	int *ptr = &retVal;
	node *temp = 0;

	while (strPost[i] != '\0'){
		// number
		if (strPost[i] >= '0' && strPost[i] <= '9'){
			temp = push(temp, strPost[i]);
		}

		// operator
		else if ((strPost[i] == '+') || (strPost[i] == '-') || (strPost[i] == '*') || (strPost[i] == '/') || (strPost[i] == '%')){
			temp = calcOperator(temp, strPost[i]);
		}

		// blank
		else if (strPost[i] == ' '){
			temp = push(temp, strPost[i]);
		}

		i++;
	}

	printf("ANSWER : ");
	while (temp != NULL){
		if (temp->key != ' '){
			printf("%c", temp->key);
		}
		temp = pop(temp);
	}
	printf("\n");

	//return retVal;
}

node *calcOperator(node *temp, char operator){
	int num[2] = { 0, 0 };
	int *ptr[2];
	int i = 0, j = 0, k = 0;
	int retVal = 0;
	int target = 0;
	int cnt = 0;

	// bring two numbers
	for (i = 1; i >= 0; i--){
		cnt = 0;
		// remove blank
		while (temp->key == ' '){
			temp = pop(temp);
		}

		// 공백 (각 아이템의 경계) 을 읽을 때 까지
		while (temp->key != ' '){
			// 자릿수를 체크하는 변수가 0 이상이라면, 기존에 있던 숫자에 10을 곱한다.
			if (cnt){
				num[i] *= 10;
				num[i] += temp->key - '0';
			}

			// 1의자리 수라면,
			else{
				num[i] = temp->key - '0';
			}

			temp = pop(temp);
			cnt++;

			if (temp == NULL){
				break;
			}
		}
	}

	// calculation
	if (operator == '+'){
		retVal = num[0] + num[1];
	}
	else if (operator == '-'){
		retVal = num[0] - num[1];
	}
	else if (operator == '*'){
		retVal = num[0] * num[1];
	}
	else if (operator == '/'){
		retVal = num[0] / num[1];
	}
	else if (operator == '%'){
		retVal = num[0] % num[1];
	}

	// 합쳐진 숫자는 int형이기 때문에 다시 string으로 만들어줘야 한다.
	while (retVal != 0){
		temp = push(temp, (retVal % 10) + '0');
		retVal /= 10;
	}

	temp = push(temp, ' ');


	return temp;
}

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

void printStack(node *front){
	node *temp = 0;
	temp = front;
		printf("\n");
	printf("\n");

	while (temp != NULL){
		printf("%c\n", temp->key);
		temp = temp->next;
	}	printf("\n");	printf("\n");
}