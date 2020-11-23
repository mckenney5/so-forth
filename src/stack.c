#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"
#include "config.h"
#include "errors.h"

static long long data_stack[MAX] = {0}; //TODO linked list?
static size_t data_index = 1; //stack pointer, should point to top (1)

//static long *return_stack = NULL;

/*
struct Dictionary {
	struct Dictionary *previous;
	struct Dictionary *next;
	char *name;
	char control_bits; //maybe make unsigned int f1:1; for a single bit flag
	void *code;
};

struct Dictionary *head = NULL;
struct Dictionary *current = NULL;

struct Dictionary dictionary[MAX]; //TODO dynamic allocation
*/
void push(const long long data){
	if(data_index == 0) data_index = 1;
	if(data_index+1 != MAX) data_stack[data_index++] = data;
	else set_error(E_OVERFLOW);
}

void show_stack(){
	size_t i = 1;
	printf("<%ld> ", data_index-1);
	for(; i < data_index; i++)
		printf("%lld ", data_stack[i]);
	fflush(stdout);
}

long long read_stack(size_t offset){
	if(data_index - offset <= 0){
		set_error(E_UNDERFLOW);
		return 0;
	} else
		return data_stack[data_index -1 -offset];
}

long long pop(size_t offset){
	if(data_index - offset <= 1){
		set_error(E_UNDERFLOW);
		return 0;
	} else
		return data_stack[--data_index - offset];
}

size_t get_index(){
	return data_index;
}

void clear_stack(){
	data_index = 1;
}

char* push_string(char* str){
// allocates the string and pushes its address and size to the data stack
	char* temp = NULL;
	temp = calloc(sizeof(char), strlen(str)+1); //makes sure it is null terminated
	
	if(temp != NULL) strcpy(temp, str); //cant be overrun since temp is one char bigger

	//push address to the stack
	push((long)temp);
	
	//push strlen to the stack
	push(strlen(temp));
	return temp;
}

void pop_string(char* str){
	if(str == NULL) set_error(E_NULL_PTR); 
	else free(str); 
}

