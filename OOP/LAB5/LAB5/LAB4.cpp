// LAB4.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <memory>

#include "Hexagon.h"
#include "Pentagon.h"
#include "Rhombus.h"
#include "Figure.h"

#include "TBINTREEITEM.h"
#include "TBINTREE.h"



int main()
{
	TBinTree<Figure> tree;
	int choice;
	std::cout << "0-Exit  1-PushPentagon  2-PushHexagon  3-PushRhombus" << std::endl << "4-Pop  5-PrintTree" << std::endl;
	while (1) {
		std::cin >> choice;
		if (choice == 0) {
			std::cout << "The programm has been finished" << std::endl;
			break;
		}
		if (choice == 1) {
			tree.push(std::shared_ptr<Figure>(new Pentagon(std::cin)));
		}
		if (choice == 2) {
			tree.push(std::shared_ptr<Figure>(new Hexagon(std::cin)));
		}
		if (choice == 3) {
			tree.push(std::shared_ptr<Figure>(new Rhombus(std::cin)));
		}
		if (choice == 4) {
			std::shared_ptr<Figure> t;
			tree.pop(1);
		}
		if (choice == 5) {
			tree.print_Tree(tree.head, 0);
		}
	}
    return 0;
}

