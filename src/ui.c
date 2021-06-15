#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "interp.h"
#include "config.h"
#include "colors.h"

#include "../libs/linenoise.h"

void ui(){
	char *inpt = NULL;
	puts(MOTD);
	while((inpt = linenoise(PROMPT)) != NULL){
		if(inpt != NULL){
			linenoiseHistoryAdd(inpt);
			if(!strcmp("bye", inpt)){
				linenoiseFree(inpt);
				break;
			} else {
				run(inpt);
				if(!get_error()) printf("%s %sok%s", PADDING, GREEN, RESET);
				set_error(0);
			}
		}
		fflush(stdout);
		linenoiseFree(inpt);
		putchar('\n');
	}
}

int from_file(char *file_name){
	size_t i = 0;
	//char *script = NULL;
	char script[MAX_SCRIPT]= {'\0'};

	char data = 0;
	FILE *fp = NULL;
	if(file_name[0] == '-' && file_name[1] == '\0')
		fp = stdin;
	else
		fp = fopen(file_name, "r");

	if(fp == NULL){ perror("soforth"); return 1;}
	while((data = fgetc(fp)) != EOF && i < MAX_SCRIPT){
		switch(data){
			case '\r': break;
			case '\t': break;
			case '\\': while(data != '\n'){data = fgetc(fp); if(data == EOF) break;} break;
			case '(': while(data != ')'){data = fgetc(fp); if(data == EOF) break;} break;
			case '\n': data = ' ';
			default:
				if(i+1 >= MAX_SCRIPT){
					puts("File too big");
					return 1;
				} else
					script[i++] = data;
		}
	}
	run(script);
	fclose(fp);
	return 0;
}

int help(){
	puts("usage: soforth <files/stdin (-)>");
	return 0;
}

int main(int argc, char **argv){
	if(argc > 1){
		if(argv[1][0] == '-' && argv[1][1] != '\0') return help();
		size_t i = 1;
		for(; argv[i] != NULL; i++)
			if(from_file(argv[i])) return 1;
	} else
		ui();
	putchar('\n');
	return 0;
}

