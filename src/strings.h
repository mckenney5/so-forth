#ifndef _USING_STRINGS_H
#define _USING_STRINGS_H

void *xmalloc(unsigned long long size);
char **tokenize(const char *inpt);
void cut(char* inpt, const size_t n);
char *dice(const char* inpt, const size_t start, const size_t end);
size_t find(char* inpt, const char c, size_t occurance);
size_t find_str(char *haystack, char *needle, size_t occurance);

#endif

