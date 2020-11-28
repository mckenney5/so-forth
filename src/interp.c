#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "stack.h"
#include "words.h"
#include "errors.h"
#include "strings.h"

static int error_id = 0;

void set_error(int error){
	error_id = error;
}

int get_error(){
	return error_id;
}

static int check_error(){
	switch(get_error()){
		case 0: break;
		case E_UNDERFLOW: fprintf(stderr, "%s underflow.", PADDING); break;
		case E_UNDEFINED_WORD: fprintf(stderr, "%s undefined word.", PADDING); break;
		case E_OVERFLOW: fprintf(stderr, "%s overflow.", PADDING); break;
		case E_NULL_PTR: fprintf(stderr, "%s null pointer.", PADDING); break;
		default: printf("%s unknown error", PADDING);
	}
	return error_id;
}
static void to_lower(char* word){
	// convert word to lowercase
	size_t i = 0;
	for(; word[i] != '\0'; i++)
		if(word[i] >= 'A' && word[i] <= 'Z') word[i] = word[i] + 32;
}
int is_digit(const char* input){
	if(input[0] == '-' && input[1] >= '0' && input[1] <= 57) return 1;
	else if(input[0] >= '0' && input[0] <= '9') return 1;
	else return 0;
}

int is_operator(const char* input){
	if(input[1] != '\0') return 0;
	switch(input[0]){
		case '+':
		case '-':
		case '/':
		case '*':
		case '<':
		case '>':
		case '=':
		case '%': return 1; //TODO check if this is standard
		default:
			return 0;
	}
	
}

void handle_operator(char op){
	long n2 = pop(0);
	long n1 = pop(0);

	switch(op){
		case '+': push(n1 + n2); break;
		case '-': push(n1 - n2); break;
		case '/': push(n1 / n2); break;
		case '*': push(n1 * n2); break;
		case '>': if(n1 > n2) push(_TRUE); else push(_FALSE); break;
		case '<': if(n1 < n2) push(_TRUE); else push(_FALSE); break;
		case '=': if(n1 == n2) push(_TRUE); else push(_FALSE); break;
		case '%': push(((n1 % n2) + n2) % n2); break; //makes it compatible with gForth
		default:
			puts("Error in handle_operator");
			return;
	}
}


void run(char *input){
	if(!strcmp(input, "")) return;
	size_t i = 0, l=0, occur = 1;;
	char *temp = NULL;
	char **t = tokenize(input);

	//size_t count = 0; //count commands
	for(; t[i] != NULL; i++){
		//count++; //TODO use this for errors
		to_lower(t[i]);
		if(dictionary_search(t[i]));
		else if(check_words(t[i]));
		else if(!strcmp(" ", t[i]));
		else if(!strcmp("bye", t[i])){ putchar('\n'); exit(0);}
		else if(is_operator(t[i])) handle_operator(t[i][0]);
		//FIXME else if(!strcmp(".\"", t[i])){ for(i++; strcmp(t[i], "\""); i++){ if(t[i] == NULL) break; else printf("%s ", t[i]);}} //display a string
		//FIXME else if(!strcmp("s\"", t[i])){ temp = dice(input, find_str(t[i], "s\"", occur), find(t[i], '"', occur)); push_string(temp);} //put a string and its size on the stack
		else if(!strcmp("exit", t[i])) break; //NON-STANDARD (interpretation is undefined -so this brings the user back to the interp.)
		else if(!strcmp(":", t[i])){ i = dictionary_add(t, i);} //HACK
		else if(is_digit(t[i])) push(atoll(t[i]));

		else error_id = E_UNDEFINED_WORD;
		
		if(check_error()){ clear_stack(); break;} //if there is an error, clean the stack and stop
	}
	free(t);
	if(temp != NULL) free(temp);
}

