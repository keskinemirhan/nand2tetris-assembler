#ifndef STR_HELPER_H
#define STR_HELPER_H

#include <string.h>
#include <stdlib.h>

char* trim(char* str);
int char_index(char* str, char c);
int chars_index(char* str, char* chars);
int match_one(char c, char* chars);
char* to_binary_str(int integer, unsigned int len);
int is_number_str(char* str);

#endif
