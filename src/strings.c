#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "config.h"

void *xmalloc(unsigned long long size){
// works like malloc but exits if it fails
	void *temp = NULL;
	temp = malloc(size);
	if(temp == NULL){
		fprintf(stderr, "Error allocating memory!\n");
		exit(-1);
	} else
		return temp;
}

char **tokenize(const char *inpt){
// returns a 2D array split up by ' ', this needs to be free'd
	size_t i = 0, x=0, y=0, size = 1;
	char **tokens = NULL;
	tokens = xmalloc(sizeof(char *) * 1);
	tokens[0] = xmalloc(sizeof(char) * MAX_NAME);
	while(1){
		switch(inpt[i]){
			case ' ' :
				if(inpt[i+1] == ' ' || inpt[i+1] == '\0') break;
				tokens[x][y] = '\0';
				y = 0;
				tokens = realloc(tokens, sizeof(char *) * ++size);
				if(tokens == NULL) exit(-1);
				tokens[++x] = xmalloc(sizeof(char) * MAX_NAME+1);
				break;
			case '\0' :
				tokens[x][y] = '\0';
				y = 0;
				tokens = realloc(tokens, sizeof(char *) * ++size);
				if(tokens == NULL) exit(-1);
				tokens[++x] = NULL;
				return tokens;
				break;
			default :
				tokens[x][y++] = inpt[i];
				break;
		}
		i++;
	}
}

void cut(char* inpt, const size_t n){
// removes n chars from the start of a string
	char *temp = NULL;
	size_t size = strlen(inpt);
	temp = xmalloc(sizeof(char) * size);
	size_t i=0, l=0;
	for(i = n; inpt[i] != '\0'; i++)
		temp[l++] = inpt[i];
	strcpy(inpt, temp);
	free(temp);
}

char* dice(const char* inpt, const size_t start, const size_t end){
// makes a sub string by cutting and truncating a string, the output needs to be free'd
	size_t i=0, l=0;
	char *output = xmalloc(sizeof(char) * (end - start) +1);
	for(i = start; i != end; i++)
		output[l++] = inpt[i];
	return output;
}

size_t find(const char* inpt, const char c, const size_t occurance){
// looks for a certain char and returns its location
	size_t i = 0, count = 1;
	for(; inpt[i] != '\0'; i++){
		if(inpt[i] == c){
			if(count++ == occurance) return i;
		}
	}
	return 0; //if not found, return 0 TODO maybe change this to strlen+1?
}

size_t find_str(const char* haystack, const char* needle, const size_t occurance){
// looks for a certain char and returns its location, after n ammount of occurances FIXME
	size_t i = 0, l=0, size=strlen(needle), count=1;
	for(; haystack[i] != '\0'; i++){
		if(haystack[i] == needle[0]){
			for(l=0; 1 == 1; l++){
				if(haystack[i] != needle[l]) break;
				else if(l == size && count != occurance){
					count++;
					break;
				} else if(l == size && count == occurance) return i;
			}
		}
	}
	return 0; //if not found, return 0 TODO maybe change this to strlen+1?
}

/*
int main(){
	printf("> ");
	fflush(stdout);
	char buff[MAX_NAME] = {'\0'};
	fgets(buff, MAX_NAME-1, stdin);
	buff[strlen(buff)-1] = '\0';

	char* temp = dice(buff, 2, 5);
	printf("Dicing at %d and %d: before: '%s' | After: '%s'\n", 2, 5, buff, temp);
	free(temp);

	printf("Looking for '%s' in input: 1st occurance '%ld' 2nd: '%ld'\n", "12", find_str(buff, "12", 1), find_str(buff, "12", 2));

	printf("Looking for the 2nd '1' in the string: %ld\n", find(buff, '1', 2));

	char **tokens = tokenize(buff);
	size_t i = 0;
	for(; tokens[i] != NULL; i++)
		printf("'%s' ", tokens[i]);
	free(tokens);
	putchar('\n');
	return 0;
}
*/
