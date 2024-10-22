#ifndef PARSER_H
#define PARSER_H
#include <stdio.h>

typedef enum command_type {
    NO_COMMAND,
    INVALID_COMMAND,
    A_COMMAND,
    C_COMMAND,
    L_COMMAND
} command_type;

int has_more_commands(FILE* file);
char* advance(FILE* file); 
command_type get_command_type(char* line);
char* trim(char* line); 
char* get_symbol(char* str);
char* get_dest(char* str);
char* get_jump(char* str);
char* get_comp(char* str);

#endif
