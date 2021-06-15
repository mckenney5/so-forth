#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"
#include "colors.h"
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
	fprintf(stderr, "%s", RED);
	switch(get_error()){
		case 0: break;
		case E_UNDERFLOW: fprintf(stderr, "%s underflow.", PADDING); break;
		case E_UNDEFINED_WORD: fprintf(stderr, "%s undefined word.", PADDING); break;
		case E_OVERFLOW: fprintf(stderr, "%s overflow.", PADDING); break;
		case E_NULL_PTR: fprintf(stderr, "%s null pointer.", PADDING); break;
		default: fprintf(stderr, "%s unknown error", PADDING);
	}
	fprintf(stderr, "%s", RESET);
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

size_t make_string(char **t, size_t i){
	char *string = NULL;
	size_t size = 0;
	size_t start = ++i;
	if(t[i] == NULL){
		size = 0;
	} else {
		for(i; t[i] != NULL && t[i][strlen(t[i])-1] != '"'; i++)
			size = size + strlen(t[i]) + 1;
		if(t[i] != NULL) size = size + strlen(t[i]); //last part of the string
	}
	string = malloc(size * sizeof(char));
	if(!string){
		//TODO handle better
		push(0);
		push(0);
		return i;
	}
	string[0] = '\0';
	if(t[i] != NULL) t[i][strlen(t[i]) - 1] = '\0'; // remove the "
	for(start; start != i; start++){
		strcat(string, t[start]);
		strcat(string, " ");
	}
	if(t[start] != NULL) strcat(string, t[start]);
	push((long) (long) (char*) string);
	push(size);
	return i;
}

void run(char *input){
	if(!strcmp(input, "")) return;
	size_t i = 0, l=0, occur = 1;
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
		else if(!strcmp(".\"", t[i])){ 
			while(t[++i] != NULL && t[i][strlen(t[i])-1] != '"'){
				printf("%s ", t[i]); //print text that does not have a "
			}
			if(t[i] == NULL) break; //if we reached the end, stop
			else {
				for(l = 0; t[i][l] != '"'; l++) putchar(t[i][l]); //print a string tha has the ending "
			}
		} //display a string
		else if(!strcmp("s\"", t[i])) i = make_string(t, i);
		else if(!strcmp("exit", t[i])) break; //NON-STANDARD (interpretation is undefined -so this brings the user back to the interp.)
		else if(!strcmp(":", t[i])){ i = dictionary_add(t, i);} //HACK
		else if(is_digit(t[i])) push(atoll(t[i]));
		else if(!strcmp("\\", t[i])) t[i--] = '\0'; //remove the rest of the line for comments
		else if(!strcmp("(", t[i])) for(++i; t[i] != NULL && strcmp(")", t[i]); i++); //skip comments
		else if(!strcmp("", t[i])); //if it is null, skip

		else { 
			error_id = E_UNDEFINED_WORD;
			#ifdef DEBUGGING
				fprintf(stderr, "Unknown Word '%s' at word %ld.\n", t[i], i);
			#endif
		}
		
		if(check_error()){ clear_stack(); break;} //if there is an error, clean the stack and stop
	}
	free(t);
	if(temp != NULL) free(temp);
}

