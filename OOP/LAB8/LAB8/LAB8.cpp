// LAB8.cpp: определяет точку входа для консольного приложения.
//
#include "stdafx.h"
#include <cstdlib>
#include <iostream>
#include <memory>
#include <stdlib.h>
#include <windows.h>
#include <stdio.h>
#include "process.h" 

#include "Hexagon.h"
#include "Pentagon.h"
#include "Rhombus.h"
#include "Figure.h"

#include "TBINTREEITEM.h"
#include "TBINTREE.h"

#include "TIterator.h"

#include "TAllocationBlock.h"

TIterator <BinTreeItem <Figure>, Figure> OLEG(TIterator <BinTreeItem <Figure>, Figure> elem)
{
	if (elem.node_ptr == NULL)
		return elem;
	std::shared_ptr <Figure> nowelem = elem.operator->();
	nowelem->Print();
	if (elem.node_ptr->GetRightSon() != NULL)
	{
		elem.operator++();
		OLEG(elem);
		elem.operator*();
	}
	if (elem.node_ptr->GetLeftSon() != NULL)
	{
		elem.operator--();
		OLEG(elem);
	}
	return elem;
}



void TestAllocationBlock()
{
	TAllocationBlock allocator(sizeof(BinTreeItem <Figure>), 10);

	Rhombus *a1 = nullptr;
	Rhombus *a2 = nullptr;
	Pentagon *a3 = nullptr;
	Pentagon *a4 = nullptr;
	Hexagon *a5 = nullptr;


	a1 = (Rhombus*)allocator.allocate(); *a1 = Rhombus(1, 2, 3); std::cout << "a1 pointer value:" << *a1 << std::endl;
	a2 = (Rhombus*)allocator.allocate(); *a2 = Rhombus(1, 2, 4); std::cout << "a2 pointer value:" << *a2 << std::endl;
	a3 = (Pentagon*)allocator.allocate(); *a3 = Pentagon(3); std::cout << "a3 pointer value:" << *a3 << std::endl;

	allocator.deallocate(a1);
	allocator.deallocate(a3);

	a4 = (Pentagon*)allocator.allocate(); *a4 = Pentagon(4); std::cout << "a4 pointer value:" << *a4 << std::endl;
	a5 = (Hexagon*)allocator.allocate(); *a5 = Hexagon(5); std::cout << "a5 pointer value:" << *a5 << std::endl;
	std::cout << "a1 pointer value:" << *a1 << std::endl;
	std::cout << "a2 pointer value:" << *a2 << std::endl;
	std::cout << "a3 pointer value:" << *a3 << std::endl;

	allocator.deallocate(a2);
	allocator.deallocate(a4);
	allocator.deallocate(a5);
}

HANDLE hSemaphore;
LONG cMax = 8;
LONG dwCounter = 0;


struct Data {
	TBinTree<Figure> *tree;
};

TBinTree<Figure> * Sort(TBinTree<Figure> * tree)
{
	int choice;
	std::cout << "0-Exit  1-PushPentagon  2-PushHexagon  3-PushRhombus" << std::endl << "4-Pop  5-PrintTree" << std::endl;
	while (1) {
		std::cin >> choice;
		if (choice == 0) {
			std::cout << "The Enter has been finished" << std::endl;
			break;
		}
		if (choice == 1) {
			tree->push(std::shared_ptr<Figure>(new Pentagon(std::cin)));
		}
		if (choice == 2) {
			tree->push(std::shared_ptr<Figure>(new Hexagon(std::cin)));
		}
		if (choice == 3) {
			tree->push(std::shared_ptr<Figure>(new Rhombus(std::cin)));
		}
		if (choice == 4) {
			double del;
			std::cin >> del;
			tree->head = tree->pop(tree->head, del);
		}
		if (choice == 5) {
			tree->print_Tree(tree->head, 0);
		}
	}
	return tree;
}


DWORD WINAPI ThreadProc(CONST LPVOID lpParam) {
	Data * in = reinterpret_cast<Data*>(lpParam);
	in->tree = (new TBinTree<Figure>);
	Sort(in->tree);
	ExitThread(0);
}

VOID Error(CONST HANDLE hStdOut, CONST LPCWSTR szMessage) {
	DWORD dwTemp;
	TCHAR szError[256];
	WriteConsole(hStdOut, szMessage, lstrlen(szMessage), &dwTemp, NULL);
	wsprintf(szError, TEXT("LastError = %d\r\n"), GetLastError());
	WriteConsole(hStdOut, szError, lstrlen(szError), &dwTemp, NULL);
	ExitProcess(0);
}

int main()
{

	Data * data = new (Data);

	DWORD dwTemp, i;
	HANDLE hThread;
	CONST HANDLE hStdOut = GetStdHandle(STD_OUTPUT_HANDLE);


	hThread = CreateThread(NULL, 0, &ThreadProc, (LPVOID)data, 0, NULL);
	if (NULL == hThread) {
		Error(hStdOut, TEXT("Failed to create thread.\r\n"));
	}

	WaitForSingleObject(hThread, INFINITE);
	CloseHandle(hThread);




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
			double del;
			std::cin >> del;
			tree.head = tree.pop(tree.head, del);
		}
		if (choice == 5) {
			tree.print_Tree(tree.head, 0);
		}
	}
	std::shared_ptr<BinTreeItem<Figure>> head = tree.head;
	TIterator <BinTreeItem <Figure>, Figure> a(head);
	OLEG(a);
	TestAllocationBlock();
	return 0;
}