#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "stack.h"
#include "words.h"
#include "errors.h"

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
	char *t = NULL;
	//size_t count = 0; //count commands
	t = strtok(input, " ");
	for(; t != NULL; t = strtok(NULL, " ")){
		//count++; //TODO use this for errors
		to_lower(t);
		if(check_words(t));
		else if(!strcmp(" ", t));
		else if(!strcmp("bye", t)){ putchar('\n'); exit(0);}
		else if(is_operator(t)) handle_operator(t[0]);
		else if(!strcmp(".\"", t)){ t = strtok(NULL, "\""); printf("%s", t);} //put a string and its size on the stack
		else if(!strcmp("s\"", t)){ t = strtok(NULL, "\""); push_string(t);} //put a string and its size on the stack
		else if(!strcmp("exit", t)) break; //NON-STANDARD (interpretation is undefined so this brings the user back to the interp.)
		else if(is_digit(t)) push(atoll(t));

		else error_id = E_UNDEFINED_WORD;
		
		if(check_error()){ clear_stack(); break;} //if there is an error, clean the stack and stop
	}
	if(!get_error()) printf("%s ok", PADDING);
	error_id = 0;
}

