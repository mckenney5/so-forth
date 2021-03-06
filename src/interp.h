#ifndef _USING_INTERP_H
#define _USING_INTERP_H

void set_error(int error);
int get_error();
int is_digit(const char* input);
int is_operator(const char* input);
void handle_operator(char op);
void run(char *input);

#endif
