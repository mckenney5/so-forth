#include <stdio.h>

#include "config.h"

static long i_stack[MAX] = {0};
static size_t index_i = 1; //stack pointer, should point to top (0)

void push(const long data){
	if(index_i == 0) index_i = 1;
	i_stack[index_i++] = data;
}

void show_stack(){
	size_t i = 1;
	printf("<%ld> ", index_i-1);	
	for(; i < index_i; i++)
		printf("%ld ", i_stack[i]);
	printf("\n");
}

long read_stack(){
	return i_stack[index_i-1];
}

long pop(){
	if(index_i == 1){
		puts("Stack Underflow");
		return -666;
	} else
		return i_stack[--index_i];
}

size_t get_index(){
	return index_i;
}

