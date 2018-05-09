#ifndef __STRUCT_CONTROL_AGRO_H__
#define __STRUCT_CONTROL_AGRO_H__

#include "input.h"
#include "output.h"

typedef struct Node_in
{
	int id;
	struct Node_in *next;
	Input *input;

} Node_in;

typedef struct Node_out
{
	int id;
	struct Node_out *next;
//	Output *output;
} Node_out;

Node_in *create_in(void){
	return (Node_in *) malloc(sizeof(Node_in));
}

int delete_in(Node_in *nodo){
	if(nodo != NULL){
		free(nodo);
		return 0;
	}
	else{
		return -1;
	}
}

int push_in(Node_in *lista , Node_in *ptr_nodo){
	if(lista != NULL){
		ptr_nodo->next = lista;
		lista = ptr_nodo;
		return 0;
	}
	else{
		return -1;
	}
}

int push_out(Node_out *lista , Node_out *ptr_nodo){
	if(lista != NULL){
		ptr_nodo->next = lista;
		lista = ptr_nodo;
		return 0;
	}
	else{
		return -1;
	}
}

#endif