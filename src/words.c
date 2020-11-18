/* words should be implemented here */
#include <stdio.h>
#include <string.h>

#include "interp.h"
#include "stack.h"
#include "config.h"

static void dup(){
//copys the top most data on the stack
	push(read_stack());
}

int check_words(char *word){
/* this function should be called first from run()
 * returns 1 if a command was found, returns 0 if it wasnt
 * add new words above and here, dont forget to add them to the header
 */
	long temp = 0;
	// convert word to lowercase
	size_t i = 0;
	for(; word[i] != '\0'; i++){
		if(word[i] >= 'A' && word[i] <= 'Z') word[i] = word[i] + 32;
	}

	//TODO check for user defined words first

	if(!strcmp("dup", word)) dup();
	else if(!strcmp("spaces", word)){ temp = pop(); if(!get_error()) for(i=0; (long)i < temp; i++) putchar(' ');}
	else if(!strcmp("emit", word)) putchar((char)pop());
	else return 0;
	
	return 1;
}
