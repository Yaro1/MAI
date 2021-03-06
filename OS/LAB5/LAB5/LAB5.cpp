// LAB5.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include "windows.h"
#include <iostream>
#include <Windows.h>
#include <stdio.h>
#include <conio.h>

#include "LAB5_DLL.h"

int main()
{
	stack * my_stack = (stack *)malloc(sizeof(stack));
	printf("Load library and function's is succes!\n");
	printf("Choose act.\n");
	printf("a : init stack\nb : push stack\nc : pop stack\nd : stkTop\ne : gettop\nf : is empty stack\ng : print stack\nh : exit from programm\ni : help\n");
	while (1)
	{
		char choice;
		scanf("%c", &choice);
		switch (choice)
		{
		case 'a':
		{
			init(my_stack);
			continue;
		}
		case 'b':
		{
			float add_elem;
			scanf("%f", &add_elem);
			int err = push(my_stack, add_elem);
			if (err != 0)
				printf("In add element somthing was wrong\n");
			continue;
		}
		case 'c':
		{
			float del_elem;
			del_elem = pop(my_stack);
			printf("Delete element %f\n", del_elem);
			continue;
		}
		case 'd':
		{
			float top;
			top = stkTop(my_stack);
			printf("Top element in stack is %f\n", top);
			continue;
		}
		case 'e':
		{
			float get_top;
			get_top = gettop(my_stack);
			printf("Taked element %f\n", get_top);
			continue;
		}
		case 'f':
		{
			int empty = isempty(my_stack);
			if (empty == 1)
				printf("Stack is empty\n");
			else
				printf("Stack is not empty\n");
			continue;
		}
		case 'g':
		{
			stkPrint(my_stack);
			continue;
		}
		case 'h':
		{
			free(my_stack);
			return 0;
		}
		case 'i':
		{
			printf("a : init stack\nb : push stack\nc : pop stack\nd : stkTop\ne : gettop\nf : is empty stack\ng : print stack\nh : exit from programm\ni : help\n");
			continue;
		}
		}
	}
	return 0;
}