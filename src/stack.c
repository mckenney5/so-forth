#include <stdio.h>
#include <stdlib.h>

#include "config.h"

static long l_stack[MAX] = {0};
static size_t l_index = 1; //stack pointer, should point to top (0)

//static char* s_stack = NULL;
//static size_t s_index = 0;

void push(const long data){
	if(l_index == 0) l_index = 1;
	l_stack[l_index++] = data;
}

void show_stack(){
	size_t i = 1;
	printf("<%ld> ", l_index-1);	
	for(; i < l_index; i++)
		printf("%ld ", l_stack[i]);
	printf("\n");
}

long read_stack(){
	return l_stack[l_index-1];
}

long pop(){
	if(l_index == 1){
		puts("Stack Underflow");
		return 0;
	} else
		return l_stack[--l_index];
}

/*void init(){
	//initalize string stack as needed
}*/

size_t get_index(){
	return l_index;
}

