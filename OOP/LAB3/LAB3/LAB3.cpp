// LAB3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <cstdlib>

#include <iostream>

#include "Rhombus.h"

#include "TBINTREEITEM.h"

#include "TBINTREE.h"


int main()
{
	TBinTree tree;

	for (; 1;)
	{
		char choice;
		std::cin >> choice;
		if (choice == 'r')
		{
			tree.push(Rhombus(std::cin));
		}

		if (choice == 'h')
		{
			tree.push(Hexagon(std::cin));
		}

		if (choice == 'p')
		{
			tree.push(Pentagon(std::cin));
		}
		if (choice == 'q')
		{
			break;
		}
		if (choice == 's')
		{
			tree.print_Tree(tree.head, 0);
		}

	}


	/*
	tree.push(Rhombus(1, 2, 2));

	tree.push(Pentagon(1));

	tree.push(Hexagon(3));

	tree.push(Rhombus(1, 1, 1));


	//std::cout << tree;
	tree.print_Tree(tree.head, 0);

	Rhombus t;
	tree.pop(2);

	std::cout << tree;
	*/

	/*
	t = tree.pop(); std::cout << t;

	t = tree.pop(); std::cout << t;

	t = tree.pop(); std::cout << t;
	*/
	return 0;
}

