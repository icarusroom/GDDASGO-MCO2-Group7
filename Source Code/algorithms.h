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
