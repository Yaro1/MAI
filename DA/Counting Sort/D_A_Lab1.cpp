// D_A_Lab1.cpp: определяет точку входа для консольного приложения.
//

#include "stdafx.h"
#include <iostream>
#include <string>
#include "myvector.h"



void count_sort(vector * my_Data, char *s, vector * ans_Data)
{
	int mas[16];
	for (int i = 0; i < 16; i++)
		mas[i] = 0;
	for (int i = 0; i < my_Data->size; i++)
	{
		if (s[i] == 'a' || s[i] == 'b' || s[i] == 'c' || s[i] == 'd' || s[i] == 'e' || s[i] == 'f')
		{
			if (s[i] == 'a')
				mas[10]++;

			else if (s[i] == 'b')
				mas[11]++;

			else if (s[i] == 'c')
				mas[12]++;

			else if (s[i] == 'd')
				mas[13]++;

			else if (s[i] == 'e')
				mas[14]++;

			else if (s[i] == 'f')
				mas[15]++;
			continue;
		}
		mas[s[i] - '0']++;
	}
	for (int i = 1; i < 16; i++)
	{
		mas[i] += mas[i - 1];
	}
	for (int i = my_Data->size - 1; i >= 0; i--)
	{
		if (s[i] == 'a' || s[i] == 'b' || s[i] == 'c' || s[i] == 'd' || s[i] == 'e' || s[i] == 'f')
		{
			if (s[i] == 'a')
			{
				ans_Data->data[mas[10] - 1] = my_Data->data[i];
				mas[10]--;
			}
			else if (s[i] == 'b')
			{
				ans_Data->data[mas[11] - 1] = my_Data->data[i];
				mas[11]--;
			}
			else if (s[i] == 'c')
			{
				ans_Data->data[mas[12] - 1] = my_Data->data[i];
				mas[12]--;
			}
			else if (s[i] == 'd')
			{
				ans_Data->data[mas[13] - 1] = my_Data->data[i];
				mas[13]--;
			}

			else if (s[i] == 'e')
			{
				ans_Data->data[mas[14] - 1] = my_Data->data[i];
				mas[14]--;
			}

			else if (s[i] == 'f')
			{
				ans_Data->data[mas[15] - 1] = my_Data->data[i]; // dvmesto -1 napisal -i
				mas[15]--;
			}
		}
		else
		{
			ans_Data->data[mas[s[i] - '0'] - 1] = my_Data->data[i];
			mas[s[i] - '0']--;
		}
	}
}

int main()
{
	vector * my_data;
	char key[33];
	unsigned long long int value;
	my_data = create_vector(0);
	for (int j = 0; /*std::cin >> key >> value*/j<4; j++) {
		std::cin >> key >> value;
		Data * now_data = new Data;
		now_data->value = value;
		for (int i = 0; i < 33; i++)
		{
			now_data->key[i] = key[i];
		}
		now_data->key[32] = 0;
		resize_vector(my_data, j + 1);
		save_vector(my_data, j, now_data);
	}
	//char *s = (char *)malloc(sizeof(char) * my_data->size);
	char s[4];
	vector * answer = create_vector(my_data->size);
	//resize_vector(answer, 4);
	for (int discharge = 31; discharge >= 0; discharge--)
	{
		for (int i = 0; i < my_data->size; i++)
			s[i] = my_data->data[i].key[discharge];

		count_sort(my_data, s, answer);
		std::cout << std::endl << discharge << std::endl;
		for (int i = 0; i < answer->size; i++)
			std::cout << answer->data[i].key << " " << answer->data[i].value << std::endl;
		//my_data = answer;
// 19
	}
	std::cout << std::endl << std::endl;
	for (int i = 0; i < answer->size; i++)
		std::cout << answer->data[i].key << " " << answer->data[i].value << std::endl;
	return 0;
}