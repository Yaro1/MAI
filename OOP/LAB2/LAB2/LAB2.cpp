// LAB2.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"

#include <cstdlib>

#include <iostream>

#include "Rhombus.h"

#include "TBINTREEITEM.h"

#include "TBINTREE.h"

// Simple stack on pointers

int main(int argc, char** argv) {

	TBinTree tree;

	tree.push(Rhombus(1, 1, 1));

	tree.push(Rhombus(2, 2, 2));

	tree.push(Rhombus(3, 3, 3));

	std::cout << tree;

	Rhombus t;
	tree.pop(2);

	std::cout << tree;
/*
	t = tree.pop(); std::cout << t;

	t = tree.pop(); std::cout << t;

	t = tree.pop(); std::cout << t;
*/
	return 0;
}