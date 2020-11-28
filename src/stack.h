#ifndef _USING_STACK_H
#define _USING_STACK_H

size_t dictionary_add(char **input, size_t index);
int dictionary_search(char* word);
void push(const long data);
void show_stack();
long long read_stack(size_t offset);
long long pop(size_t offset);
size_t get_index();
void clear_stack();
char* push_string(char* str);
void pop_string(char *str);

#endif
