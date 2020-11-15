/* words should be implemented here */
#include <stdio.h>
#include <string.h>

#include "interp.h"
#include "stack.h"
#include "config.h"

void dup(){
//copys the top most data on the stack
	push(read_stack());
}

int check_words(char *word){
/* this function should be called first from run()
 * returns 1 if a command was found, returns 0 if it wasnt
 * add new words above and here, dont forget to add them to the header
 */
	// convert word to lowercase
	size_t i = 0;
	for(; word[i] != '\0'; i++){
		if(word[i] >= 'A' && word[i] <= 'Z') word[i] = word[i] + 32;
	}

	//TODO check for user defined words first

	if(!strcmp("dup", word)){ dup(); return 1;}
	else return 0;

}
