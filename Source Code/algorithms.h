/*****************************************************
YOU ARE NOT ALLOWED TO MODIFY THE FUNCTION PROTOTYPES
*****************************************************/
#include "main.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void infixToPostfix(char *infix, char *postfix) {
	stack *p_Operators = createStack(100);	//STACK FOR OPERATORS
	strcpy(postfix, "");		//RESET POSTFIX

	int i = 0;
	
	//READ THE INFIX CHARS
	while(infix[i] != '\0'){	
		char *str_Copy = malloc(257);	//MUST CREATE A NEW STRING EVERY LOOP OR IT'LL COPY PREVIOUS STRING'S VALUE. IDEALLY SIZE MALLOC (NUMBER OF LARGEST INTEGER DIGITS) COULD BE ENOUGH SINCE NEW STRING EVERY LOOP
		str_Copy[i] = infix[i];
		
		switch (distinguishChar(infix[i])){
			//SPACES
			case 0:
				break;
			//NUMBERS
			case 1:
				str_Copy[i+1] = '\0';
				strcat(postfix, (str_Copy+i));	//DIRECTLY ADD THE CHAR
				if(infix[i+1] == ' '){
					strcat(postfix, " ");		//CONCAT A SPACE WHEN IT'S THE LAST DIGIT
				}
				break;
			//OPERATORS
			case 2:
				//EXTARCT THE OPERATOR
				//SINGLE DIGIT OPERATORS +, -, !, /...
				if (infix[i+1] == ' '){
					str_Copy[i+1] = '\0';
					//printf("SINGLE: %s", str_Copy+i);
				}
				//DOUBLE DIGIT OPERATORS !=, ==, &&, ||...
				else{
					str_Copy[i+1] = infix[i+1];
					str_Copy[i+2] = '\0';
					//printf("DOUBLE: %s", str_Copy+i);
				}


				//HANLE WHAT TO DO WITH THE OPERATOR AND STACK
				//PUSH IF EMPTY
				if (stackEmpty(p_Operators)){
					push(&p_Operators, "(");
					push(&p_Operators, (str_Copy+i));
				}

				//PUSH IF (
				else if (str_Copy[i] == '('){
					push(&p_Operators, (str_Copy+i));
				}
				
				//IF ), KEEP POPPING UNTIL (
				else if (str_Copy[i] == ')'){
					while (top(p_Operators)[0] != '(' ){
						strcat(postfix, pop(&p_Operators));
						strcat(postfix, " ");
					}
					//POP THE ( BUT DON'T STORE IT
					pop(&p_Operators);
					//NO NEED TO ADD ) FROM STR_COPY
				}
				
				//PUSH IF GREATER PRECEDENCE	
				else if(getPrecedence(str_Copy+i) > getPrecedence(top(p_Operators))){
					push(&p_Operators, (str_Copy+i));
				}
				
				//POP LOOP IF <= PRECEDENCE
				else if (getPrecedence(str_Copy+i) <= getPrecedence(top(p_Operators))){
					//POP ALL LOWER/EQUAL PRECEDENCE OR UNTIL ( 
					while (getPrecedence(str_Copy+i) <= getPrecedence(top(p_Operators)) && top(p_Operators)[0] != '('){
						strcat(postfix, pop(&p_Operators));
						strcat(postfix, " ");
					}
					//PUSH NOW THAT IT'S THE GREATEST PRECEDENCE
					push(&p_Operators, str_Copy+i);
				}


				//MOVE THE POINTER TO ADJUST FOR 2 DIGIT OPERATORS
				if (strlen(str_Copy+i) == 2){
					i++;	//AVOID READING THE 2ND DIGIT OF AN 2 DIGIT OPERATOR '=' OF !=, <=, >=...
				}
				break;
			default:
				break;
		}
		//INCREMENT THE POINTER FOR READING THE NEXT CHAR
		i++;
	}
	//STRING PARSING LOOP END

	//DUMP ALL REMAINING OPERATORS
	while (!stackEmpty(p_Operators)){
		strcat(postfix, " ");
		strcat(postfix, pop(&p_Operators));
	}

	cleanUpString(postfix);
}

int evaluatePostfix(char *postfix) {
	//return evaluatePostfixWithoutQueue(postfix);
	/*
	//NOT USING STACK/QUEUE. IT ADDS MORE STEPS TO STORE STRING THEN RECONVERT TO INT. JUST CONVERT AND USE INT ARRAY DIRECTLY
	int n_Temp = 0;			//TEMPORARY INT STORAGE
	int n_L, n_R;			//THE LEFT AND RIGHT INT FOR COMPUTATION
	queue* p_Operands = createQueue(257);	//THE OPERANDS CONTAINER. CAN BE SWITCHED FOR QUEUE
	int n_Pointer = -1;		//THE STARTING POINTER INDEX

	int i = 0;	//THE CHAR INDEX

	//turn string into an integer array
	int n_Length = strlen(postfix);
	int *p_Result = (int*)malloc(n_Length*sizeof(int));
	for(i=0; i<n_Length; i++)
	p_Result[i] = postfix[i] - 48;


	//READ THE STRING
	while(postfix[i] != '\0'){
		//IF A NUMBER
		if (isDigit(postfix[i])){
			n_Temp += postfix[i] - 48;
			
			//CHECK IF IT'S THE LAST DIGIT THEN STORE
			if(!isDigit(postfix[i+1])){
				n_Pointer++;
				//a_Operands[n_Pointer] = n_Temp;
				enqueue(&p_Operands, (n_Temp+i));
			}
			//ELSE PREPARE TO ADD MORE DIGITS
			else{
				n_Temp *= 10;
			}
		}

		//JUST REFRESH IF SPACE
		else if (postfix[i] == ' '){
			n_Temp = 0;
		}

		//IF AN OPERATOR
		else{
			n_R = tail(p_Operands);//a_Operands[n_Pointer];	//SET THE CURRENT AS RIGHT
			//n_Pointer--;
			n_L = head(p_Operands);//a_Operands[n_Pointer];	//SET THE PREVIOUS AS LEFT


			switch(postfix[i]){
				case '+':
					n_Temp = n_L + n_R;
					break;
				case '-':
					n_Temp = n_L - n_R;
					break;
				case '*':
					n_Temp = n_L * n_R;
					break;
				case '/':
					if (n_R == 0){
						//ERROR FOR DIVIDING BY ZERO
						return -999;
					}
					n_Temp = n_L / n_R;
					break;
				case '&':
					//&&
					n_Temp = n_L && n_R;
					i++;	//AVOID READING 2nd &
					break;
				case '|':
					n_Temp = n_L || n_R;
					i++;	//AVOID READING 2nd |
					break;
				case '=':
					//==
					n_Temp = n_L == n_R;
					i++;	//AVOID READING 2nd =
					break;
				case '!':
					//!=
					if (postfix[i+1] == '='){
						n_Temp = n_L != n_R;
						i++;	//AVOID READING =
					}
					//!
					else{
						n_Temp = !n_R;
						n_Pointer++;	//MOVE THE POINTER BACK TO USE RIGHT'S CONTAINER.
					}
					break;
				case '<':
					//<=
					if(postfix[i+1] == '='){
						n_Temp = n_L <= n_R;
						i++;	//AVOID READING =
					}
					//<
					else{
						n_Temp = n_L < n_R;
					}
					break;
				case '>':
					//>=
					if(postfix[i+1] == '='){
						n_Temp = n_L >= n_R;
						i++;	//AVOID READING =
					}
					//>
					else{
						n_Temp = n_L > n_R;
					}
					break;
				default:
			}
			//printf("(%d)", n_Temp);		//RESULT OF EVERY CALC
			enqueue(&p_Operands, n_Temp); //a_Operands[n_Pointer] = n_Temp;		//OVERRIDE THE LEFT'S CONTAINER
		}
		i++;
	}

	dequeue(&p_Operands);	//SINCE ALWAYS OVERRIDING THE LEFT, FINAL VALUE IS AT THE BOTTOM
*/
	
	int n_Temp = 0;                          //temp int storage
	char c_Temp;                        
	//char c_TempNext;
	int n_TempResult;
	int n_L, n_R;                            //L & R int for computation
	queue* p_Operators = createQueue(257);   //Creates a queue for operators
	stack* p_Operands = createStack(257);    //Creates a stack for operands
	stack* p_TempResult = createStack(257); //Stack if postfix cannot be solved in one go
	int n_Pointer = 0;                       //starting pointer index

	int i = 0;	//index for postfix

	//loops until postfix is completely solved
	while(postfix[i] != '\0'){

		//keeps looping until the postfix is an operator followed by an operand
		while(!(isDigit(postfix[i]) && !isDigit(postfix[i-2]))){
			
			//if postfix value in i is a digit, add it to the stack
			if (isDigit(postfix[i])){
				n_Temp += postfix[i] - 48;

				//if slot after current digit is a digit, loop to keep adding values.
				while(isDigit(postfix[i+1])){
					i++;
					n_Temp *= 10;
					n_Temp += postfix[i] - 48;
				}

				push(&p_Operands, n_Temp);
			}

			//if postfix value is a space, disregard it
			else if (postfix[i] == ' '){

			}

			//if postfic value in i is an operator, add it to the queue
			else{
				c_Temp = postfix[i];
				
				enqueue(&p_Operators, c_Temp);
			}

		//increments index to move on to the next slot in the postfix array.
		i++;
		}

		//evaluation step
		//loops until all values in the stack and queue are used up
		while(!queueEmpty(p_Operators) && !stackEmpty(p_Operands)){
			n_R = pop(&p_Operands);
			n_L = pop(&p_Operands);

			switch(dequeue(&p_Operators)){
				case '+':
					n_Temp = n_L + n_R;
					break;
				case '-':
					n_Temp = n_L - n_R;
					break;
				case '*':
					n_Temp = n_L * n_R;
					break;
				case '/':
					if (n_R == 0){
						//ERROR FOR DIVIDING BY ZERO
						return -999;
					}
					n_Temp = n_L / n_R;
					break;
				case '&':
					//&&
					n_Temp = n_L && n_R;
					i++;	//AVOID READING 2nd &
					break;
				case '|':
					n_Temp = n_L || n_R;
					i++;	//AVOID READING 2nd |
					break;
				case '=':
					//==
					n_Temp = n_L == n_R;
					i++;	//AVOID READING 2nd =
					break;
				case '!':
					//!=
					if (postfix[i+1] == '='){
						n_Temp = n_L != n_R;
						i++;	//AVOID READING =
					}
					//!
					else{
						n_Temp = !n_R;
						n_Pointer++;	//MOVE THE POINTER BACK TO USE RIGHT'S CONTAINER.
					}
					break;
				case '<':
					//<=
					if(postfix[i+1] == '='){
						n_Temp = n_L <= n_R;
						i++;	//AVOID READING =
					}
					//<
					else{
						n_Temp = n_L < n_R;
					}
					break;
				case '>':
					//>=
					if(postfix[i+1] == '='){
						n_Temp = n_L >= n_R;
						i++;	//AVOID READING =
					}
					//>
					else{
						n_Temp = n_L > n_R;
					}
					break;
				default:
			}
		}
			
			
			push(p_TempResult, n_Temp);		//OVERRIDE THE LEFT'S CONTAINER
		
	}

	return p_Operands[0];	//SINCE ALWAYS OVERRIDING THE LEFT, FINAL VALUE IS AT THE BOTTOM
	
}

//supposedly for the operators with 2 slots
/*
				//if operator has more than 1 slot in the post fix
				if(!isDigit(postfix[i+1]) && postfix[i+1] != ' '){
					i++;
					strcpy(c_TempNext, postfix[i]); 
					strcat(c_Temp, c_TempNext);
				}*/
