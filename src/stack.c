#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"
#include "strings.h"
#include "config.h"
#include "errors.h"

static long long data_stack[MAX] = {0}; //TODO linked list?
static size_t data_index = 1; //stack pointer, should point to top (1)

//static long *return_stack = NULL;


struct Dictionary {
	//struct Dictionary *previous;
	//struct Dictionary *next;

	//int precedence:1; //single bit flag - checks if it runs at compile time
	//int smudge:1; //for a single bit flag - checks if the word is enabled
	
	char name[MAX_NAME];
	char code[MAX]; //TODO compile
	//char parameters[MAX]; variables
} ;

//struct Dictionary *head = NULL;
//struct Dictionary *current = NULL;
static size_t dict_index = 1;
static struct Dictionary dictionary[MAX]; //TODO dynamic allocation

size_t dictionary_add(const char** inpt, size_t index){
// adds a user made word to the dictionary
	size_t size = MAX;
	size_t i = index;
	for(; strcmp(inpt[i], ";"); i++){
		if(inpt[i] == NULL) return i;
	}

	// set name
	strncpy(dictionary[dict_index].name, inpt[index+1], MAX_NAME-1);

	size = (i * MAX_NAME) +1;
	char *t = xmalloc(sizeof(char) * size);
	
	// put the code into t by getting the tokens between ': word' and ' ;'
	for(index += 2; strcmp(inpt[index], ";"); index++){ //TODO check bounds
		strncat(t, " ", MAX_NAME);
		strncat(t, inpt[index], MAX_NAME);
	}
	
	// set code
	strncpy(dictionary[dict_index].code, t, MAX);

	// free t since it is not needed anymore
	free(t);

	// move stack pointer
	dict_index++;

	// return the new index
	return index;
}

int dictionary_search(const char* word){
//searches through the user defined words, then runs it if found and returns 1, else return 0
	if(dict_index == 1) return 0;
	size_t i = dict_index;
	for(; i > 0; i--){
		if(!strcmp(word, dictionary[i].name)){
			run(dictionary[i].code); //TODO check for infinite recursion before a stack overflow
			return 1;
		}
	}
	return 0;
}

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

long long read_stack(const size_t offset){
	if(data_index - offset <= 0){
		set_error(E_UNDERFLOW);
		return 0;
	} else
		return data_stack[data_index -1 -offset];
}

long long pop(const size_t offset){
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

char* push_string(const char* str){
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

