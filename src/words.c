/* words should be implemented here */
#include <stdio.h>
#include <string.h>

#include "interp.h"
#include "stack.h"
#include "config.h"

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

	if(!strcmp("dup", word)) push(read_stack(0));
	else if(!strcmp("2dup", word)){ push(read_stack(1)); push(read_stack(1));}
	else if(!strcmp("drop", word)) pop(0);
	else if(!strcmp("2drop", word)){ pop(0); pop(0);}
	else if(!strcmp("spaces", word)){ temp = pop(0); if(!get_error()) for(i=0; (long)i < temp; i++) putchar(' ');}
	else if(!strcmp("emit", word)) putchar((char)pop(0));
	else if(!strcmp("cr", word)) putchar('\n');
	else if(!strcmp("space", word)) putchar(' ');

	else return 0;
	
	return 1;
}
