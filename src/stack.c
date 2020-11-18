#include <stdio.h>
#include <stdlib.h>

#include "interp.h"
#include "config.h"
#include "errors.h"

static long l_stack[MAX] = {0}; //TODO linked list?
static size_t l_index = 1; //stack pointer, should point to top (1)

//static char* s_stack = NULL;
//static size_t s_index = 0;

void push(const long data){
	if(l_index == 0) l_index = 1;
	if(l_index+1 != MAX) l_stack[l_index++] = data;
	else set_error(E_OVERFLOW);
}

void show_stack(){
	size_t i = 1;
	printf("<%ld> ", l_index-1);	
	for(; i < l_index; i++)
		printf("%ld ", l_stack[i]);
	fflush(stdout);
}

long read_stack(){
	return l_stack[l_index-1];
}

long pop(){
	if(l_index == 1){
		set_error(E_UNDERFLOW);
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

