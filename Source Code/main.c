/*****************************************************
YOU ARE NOT ALLOWED TO MODIFY THE FUNCTION PROTOTYPES
*****************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "node.h"
#include "stack.h"
#include "queue.h"
#include "algorithms.h"

//gcc -Wall -o main main.c && main
int main() {
	char str_Input[257];

	printf("CALCULATOR: \n");
	while (strcmp(str_Input, "QUIT")){
		scanf(" %s", str_Input);
		// Your code here

		stack *p_Stack = createStack(100);
	}
	printf("CLOSED PROGRAM");
}