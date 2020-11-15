#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "stack.h"
#include "words.h"

//TODO static int error_flag = 0;

int is_digit(const char* input){
	if(input[0] == '-' && input[1] > '0' && input[1] <= 57) return 1;
	else if(input[0] > '0' && input[0] <= '9') return 1;
	else return 0;
}

int is_operator(const char* input){
	if(input[1] != '\0') return 0;
	switch(input[0]){
		case '+':
		case '-':
		case '/':
		case '*':
		case '%': return 1;
		default:
			return 0;
	}
	
}

void handle_operator(char op){
	if(get_index() < 3){
		puts("Underflow.");
		return;	
	}
	switch(op){
		case '+': push(pop() + pop()); break;
		case '-': push(pop() - pop()); break;
		case '/': push(pop() / pop()); break;
		case '*': push(pop() * pop()); break;
		case '%': push(pop() % pop()); break;
		default:
			puts("Error in handle_operator");
			return;
	}
}


void run(char *input){
	char *t = NULL;
	t = strtok(input, " ");
	for(; t != NULL; t = strtok(NULL, " ")){
		if(check_words(t));
		else if(is_digit(t)) push(atoi(t));
		else if(!strcmp(" ", t));
		else if(is_operator(t)) handle_operator(t[0]);
		else if(!strcmp(".", t)) printf("%ld\n", pop()); //TODO handle underflow
		else if(!strcmp(".s", t)) show_stack();
		else printf("Unknown command '%s'\n", t);
		
	}
}

