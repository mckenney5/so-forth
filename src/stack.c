#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"
#include "config.h"
#include "errors.h"

static long l_stack[MAX] = {0}; //TODO linked list? rename to data?
static size_t l_index = 1; //stack pointer, should point to top (1)

//static long *return_stack = NULL;

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

long read_stack(size_t offset){
	if(l_index - offset <= 0){
		set_error(E_UNDERFLOW);
		return 0;
	} else
		return l_stack[l_index -1 -offset];
}

long pop(size_t offset){
	if(l_index - offset <= 1){
		set_error(E_UNDERFLOW);
		return 0;
	} else
		return l_stack[--l_index - offset];
}

/*void init(){
	//initalize string stack as needed
}*/

size_t get_index(){
	return l_index;
}

void clear_stack(){
	l_index = 1;
}

void* push_string(char* str){
// allocates the string and pushes its address and size to the data stack
	void* temp = NULL;
	temp = malloc(sizeof(char) * strlen(str));
	
	//TODO check for NULL?
	strncpy(temp, str, strlen(str));

	//push address to the stack
	push((long)temp);
	
	//push strlen to the stack
	push(strlen(str));
	return temp;
}

void pop_string(void* str){
	free(str); //TODO check error and check for NULL
}



