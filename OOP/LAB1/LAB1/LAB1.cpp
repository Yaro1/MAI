// LAB1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <cstdlib>
#include "Rhombus.h"
#include "Pentagon.h"
#include "Hexagon.h"

int main(int argc, char** argv) {
	int user_choice;
	std::cout << "Choose figure :" << std::endl << "1 = Rhombus" << std::endl << "2 = Pentagon" << std::endl << "3 = Hexagon" << std::endl << "If you want to  quit, press 4" << std::endl << "Help, press 5" << std::endl << std::endl;
	while (1)
	{
		Figure *ptr;
		std::cin >> user_choice;
		if (user_choice == 5)
		{
			std::cout << "Choose figure :" << std::endl << "1 = Rhombus" << std::endl << "2 = Pentagon" << std::endl << "3 = Hexagon" << std::endl << "If you want to  quit, press 4" << std::endl << "Help, press 5" << std::endl << std::endl;
			continue;
		}

		else if (user_choice == 4)
		{
			break;
		}
		else if (user_choice == 1)
		{
			ptr = new  Rhombus(std::cin);
		}
		else if (user_choice == 2)
		{
			ptr = new  Pentagon(std::cin);
		}
		else if (user_choice == 3)
		{
			ptr = new  Hexagon(std::cin);
		}
		ptr->Print();
		std::cout << "The square is : " << ptr->Square() << std::endl;
		delete ptr;

		std::cout << std::endl << "It's ok, press your choice" << std::endl;
	}
	return 0;
}


