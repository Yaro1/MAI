// LAB3.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <stdlib.h>
#include <windows.h>

struct Vershina{
	char key;
	int num;

	int * puti;
	int size_puti;

	Vershina * next;
	Vershina * prev;
};

struct Graf{
	Vershina * head;
	int size;
};

struct WIG {
	int * was_in_graf;
	int size;
};

struct QUE{
	int * queue;
	int size;
};

Vershina * add_elem(Vershina * elem, Vershina * new_elem, int count, int size)
{
	if (count < size)
	{
		count++;
		elem->next = add_elem(elem->next, new_elem, count, size);
	}
	else
	{
		elem = new_elem;
	}
	return elem;
}

Vershina * elem_index(Vershina * elem, int index)
{
	for (int i = 0; i < index; i++)
		elem = elem->next;
	return elem;
}


int Num_Cycle(Graf *graf, WIG * wig, Vershina * elem, Vershina * pred_elem)
{
	QUE * q = (QUE *)malloc(sizeof(QUE));
	q->queue = (int*)malloc(sizeof(int) * graf->size);
	q->size = 0;

	int cycle = 0;
	wig->was_in_graf[wig->size] = elem->num;
	wig->size++;
	Vershina * item;

	
	for (int j = 0, flag = 0; j < elem->size_puti; j++, flag = 0)
	{
		q->queue[j] = elem->puti[j] - 1;
		q->size++;
	}
	for (int l = 0; l < q->size; l++)
	{
		int flag = 0;
		item = elem_index(graf->head, q->queue[l]);
		if (item == pred_elem)
		{
			continue;
		}
		for (int k = 0; k < wig->size; k++)
		{
			Vershina * a = elem_index(graf->head, wig->was_in_graf[k]);
			if (a->key == item->key)
			{
				flag = 1;
				cycle++;
			}
		}
		if (flag == 0)
		{
			cycle += Num_Cycle(graf, wig, item, elem);
		}
	}
	return cycle;
}


int main()
{
	Graf * graf = (Graf *)malloc(sizeof(Graf));
	graf->size = 0;
	graf->head = (Vershina*)malloc(sizeof(Vershina));
	int size = 0;
	FILE *f;
	char *estr;
	char str1[2];
	char str2[2];

	f = fopen("data1.txt", "r");
	if (f == NULL)
	{
		perror("Reading file data1.txt ");
	}
	estr = fgets(str1, sizeof(str1), f);
	for (int i = 0; estr != NULL; estr = fgets(str1, sizeof(str1), f))
	{
		if ((str1[0] == ' ') || (str1[0] == '\n'))
			continue;
		Vershina * elem = (Vershina*)malloc(sizeof(Vershina));
		elem->key = str1[0];
		elem->next = NULL;
		elem->num = i;
		elem->prev = NULL;
		elem->size_puti = 0;
		graf->head = add_elem(graf->head, elem, 0, graf->size);
		graf->size++;
		i++;
	}
	fclose(f);
	
	Vershina * item = graf->head;
	for (int i = 0; i < graf->size; i++)
	{
		printf("%c\n", item->key);
		item = item->next;
	}

	item = graf->head;
	for (int i = 0; i < graf->size; i++)
	{
		item->puti = (int *)malloc(sizeof(int) * graf->size);
		item = item->next;
	}

	estr = NULL;
	f = fopen("data2.txt", "r");
	if (f == NULL)
	{
		perror("Reading file data2.txt ");
	}
	int a = 0;
	int b = 0;

	estr = fgets(str2, sizeof(str2), f);
	a = str2[0] - '0';
	estr = fgets(str2, sizeof(str2), f);
	estr = fgets(str2, sizeof(str2), f);
	b = str2[0] - '0';

	for (; estr != NULL;)
	 {
		if ((str2[0] == ' ') || (str2[0] == '\n'))
			continue;

		item = elem_index(graf->head, a - 1);
		item->puti[item->size_puti] = b;
		item->size_puti++;
		item = elem_index(graf->head, b - 1);
		item->puti[item->size_puti] = a;
		item->size_puti++;
		estr = fgets(str2, sizeof(str2), f);
		estr = fgets(str2, sizeof(str2), f);
		a = str2[0] - '0';
		estr = fgets(str2, sizeof(str2), f);
		estr = fgets(str2, sizeof(str2), f);
		b = str2[0] - '0';
	}
	fclose(f);

	
	item = graf->head;
	Vershina * prom_item;
	for (int i = 0; i < graf->size; i++, item = item->next)
	{
		printf("%c %d Number is %d: \n", item->key, item->size_puti, item->num);
		for (int j = 0; j < item->size_puti; j++)
		{
			prom_item = elem_index(graf->head,item->puti[j] - 1);
			printf("%c ", prom_item->key);
		}
		printf("\n");
	}
	int cycle;
	
	WIG * wig = (WIG *)malloc(sizeof(WIG));
	wig->size = 0;
	wig->was_in_graf = (int *)malloc(sizeof(int) * graf->size);
	cycle = Num_Cycle(graf, wig, graf->head, NULL);
	if (cycle == 0)
		printf("There is no any cycle.\n");
	else
		printf("This graf have cycle.\n");
		
    return 0;
}

