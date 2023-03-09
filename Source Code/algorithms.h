/*****************************************************
YOU ARE NOT ALLOWED TO MODIFY THE FUNCTION PROTOTYPES
*****************************************************/
#include "main.h"
#include "stack.h"
#include <string.h>
#include <stdlib.h>
#include <stdio.h>

void infixToPostfix(char *infix, char *postfix) {
	stack *p_Operators = createStack(100);
	strcpy(postfix, "");
	int n_NeedPrintSpace = 0;

	int i = 0;
	int j = 0;
	
	while(infix[i] != '\0'){	
		char *str_Copy = malloc(257);
		str_Copy[i] = infix[i];
		char *symbol = malloc(257);

		switch (distinguishChar(infix[i])){
			case 0:
				//printf("\nSpace");
				//Space
				if (n_NeedPrintSpace){
					strcat(postfix, " ");
					n_NeedPrintSpace = 0;
				}
				break;
			case 1:
				//printf("\nNum");
				n_NeedPrintSpace = 1;
				str_Copy[i+1] = '\0';
				strcat(postfix, (str_Copy+i));
				break;
			case 2:
				//printf("\nSign");
				str_Copy[i+1] = '\0';

				//push(&p_Operators, (str_Copy+i));
				
				if (stackEmpty(p_Operators)){
					//PUSH IF EMPTY
					push(&p_Operators, "(");
					push(&p_Operators, (str_Copy+i));
				}
				else if (str_Copy[i] == '('){
					//PUSH IF (
					push(&p_Operators, (str_Copy+i));
				}/*
				else if (str_Copy[i] == ')'){
					//IF ), KEEP POPPING UNTIL ( OR EMPTY
					while (*top(p_Operators) != '(' ){
						strcpy(symbol+j, pop(&p_Operators));
						symbol[j+1] = '\0';
						strcat(postfix, symbol+j);
						j++;
					}
					//POP THE (
					strcpy(symbol+j, pop(&p_Operators));
					symbol[j+1] = '\0';
					strcat(postfix, symbol+j);
					j++;
				}*/
				else if(getHierarchy(str_Copy[i]) > getHierarchy(*p_Operators->pTop->pLink->data)){
					//PUSH IF GREATER PRECEDENCE
					push(&p_Operators, (str_Copy+i));
				}/*
				else if (getHierarchy(str_Copy[i]) <= getHierarchy(*p_Operators->pTop->pLink->data)){
					//POP LOWER/EQUAL PRECEDENCE
					while (getHierarchy(*top(p_Operators))){
						getHierarchy(str_Copy[i]) > getHierarchy(*p_Operators->pTop->pLink->data)
						strcat(postfix, pop(&p_Operators));
					}
					strcat(postfix, pop(&p_Operators));
				}*/

				break;
			default:
				break;
		}

		i++;
	}

	//DUMP ALL REMAINING OPERATORS
	while (!stackEmpty(p_Operators)){
		strcat(postfix, pop(&p_Operators));
	}
	

	//printf("\nOPERATORS: "); displayStack(p_Operators);
}

int evaluatePostfix(char *postfix) {
	return evaluatePostfixWithoutQueue(postfix);
	/*
	//NOT USING STACK/QUEUE. IT ADDS MORE STEPS TO STORE STRING THEN RECONVERT TO INT. JUST CONVERT AND USE INT ARRAY DIRECTLY
	int n_Temp = 0;			//TEMPORARY INT STORAGE
	int n_L, n_R;			//THE LEFT AND RIGHT INT FOR COMPUTATION
	int a_Operands[257];	//THE OPERANDS CONTAINER. CAN BE SWITCHED FOR QUEUE
	int n_Pointer = -1;		//THE STARTING POINTER INDEX

	int i = 0;	//THE CHAR INDEX


	//READ THE STRING
	while(postfix[i] != '\0'){
		//IF A NUMBER
		if (isDigit(postfix[i])){
			n_Temp += postfix[i] - 48;
			
			//CHECK IF IT'S THE LAST DIGIT THEN STORE
			if(!isDigit(postfix[i+1])){
				n_Pointer++;
				a_Operands[n_Pointer] = n_Temp;
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
			n_R = a_Operands[n_Pointer];	//SET THE CURRENT AS RIGHT
			n_Pointer--;
			n_L = a_Operands[n_Pointer];	//SET THE PREVIOUS AS LEFT


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
					n_Temp = n_L / n_R;
					break;
				case '&':
					//&&
					n_Temp = n_L && n_R;
					i++;	//AVOID READING 2nd &
					break;
				case '|':
					//||
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
			printf("(%d)", n_Temp);
			a_Operands[n_Pointer] = n_Temp;		//OVERRIDE THE LEFT'S CONTAINER
		}
		i++;
	}

	return a_Operands[0];	//SINCE ALWAYS OVERRIDING THE LEFT, FINAL VALUE IS AT THE BOTTOM
	*/
}
