/* words should be implemented here */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"
#include "stack.h"
#include "config.h"

int check_words(char *word){
/* this function should be called first from run()
 * returns 1 if a command was found, returns 0 if it wasnt
 * add new words above and here, dont forget to add them to the header
 */
	long ltemp = 0;
	char* stemp = 0;
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
	else if(!strcmp("spaces", word)){ ltemp = pop(0); if(!get_error()) for(i=0; (long)i < ltemp; i++) putchar(' ');}
	else if(!strcmp("emit", word)) putchar((char)pop(0));
	else if(!strcmp("cr", word)) putchar('\n');
	else if(!strcmp("space", word)) putchar(' ');
	else if(!strcmp("mod", word)) handle_operator('%');
	else if(!strcmp("type", word)){ ltemp = pop(0); stemp = (char*)pop(0); for(i=0; (long)i < ltemp; i++)putchar(stemp[i]); pop_string(stemp);} //TODO check for segfaults?
	else if(!strcmp(".", word)){ ltemp = pop(0); if(!get_error()) printf("%ld", ltemp);}
	else if(!strcmp(".s", word)) show_stack();
	else if(!strcmp("*/", word)) push((read_stack(2) * read_stack(1) / pop(0)));
	else if(!strcmp("page", word)) printf("[H[2J[3J"); //TODO not portable (from bash: clear > out.txt)
	else if(!strcmp("true", word)) push(-1);
	else if(!strcmp("false", word)) push(0);
	
	
	else if(!strcmp("system", word)){ pop(0); putchar(' '); system((char*)pop(0));} //NON-STANDARD

	else return 0;
	
	return 1;
}
