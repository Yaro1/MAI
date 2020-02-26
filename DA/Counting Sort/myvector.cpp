#include "stdafx.h"
#include "myvector.h"


void fill_null(vector* v, int start, int stop) {
	for (int i = start; i != stop; ++i) {
		v->data[i].value = 0;
		// здесь должно быть зануление строки key
	}
}


vector* create_vector (int sz){
	vector * v = (vector *) malloc(sizeof(vector));
	v->size = sz;
	v->max = v->size;
	v->data = (Data *) malloc(sizeof(Data) * v->size);
	fill_null (v, 0, v->size);
	return v;
}


bool is_empty_vector (vector* v){
	return v->size == 0;
}


int size_vector (vector* v){
	return v->size;
}


Data load_vector (vector* v, int i){
	if ((i >= 0) && (i < v->size)){
		return v->data[i];
	}
}


void save_vector (vector* v, int i, Data * t){
	 if ((i >= 0) && (i < v->size)){
		v->data[i] = *t;
	}
}


void resize_vector (vector* v, int sz){
	if (v->max > sz){
	}
	else{
		v->max = sz;
		v->data = (Data *) realloc (v->data, sizeof(Data) * v->max);
	}
	v->size = sz;
	v->max = sz;
}


void destroy_vector (vector* v){
	v->size = 0;
	free (v->data);
}
