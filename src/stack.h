#ifndef _USING_STACK_H
#define _USING_STACK_H

void push(const long data);
void show_stack();
long long read_stack(size_t offset);
long long pop(size_t offset);
size_t get_index();
void clear_stack();
void* push_string(char* str);
void pop_string(void *str);

#endif
