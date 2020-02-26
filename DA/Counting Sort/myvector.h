#include "stdafx.h"
#include <stdbool.h>
#include <stdlib.h>


typedef struct{
	char key[33];
	unsigned long long int value;
} Data;

typedef struct{
	Data * data;
	int size;
	int max;
} vector;


vector* create_vector (int sz);


bool is_empty_vector (vector* v);


int size_vector (vector* v);


Data load_vector (vector* v, int i);


void save_vector (vector* v, int i, Data * t);


void resize_vector (vector* v, int sz);

void destroy_vector (vector* v);
	

void fill_null (vector* v, int start, int stop);