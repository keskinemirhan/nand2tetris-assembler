#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "str_helper.h"
#include "parser.h"

int has_more_commands(FILE* file) {
    return !feof(file);
}

char* advance(FILE* file) {
    char* line = (char *) malloc(sizeof(char)*500);
    fgets(line, 500, file);
    return line;
}

int match_L(char* word) {
    size_t len = strlen(word);
    return len > 0 && word[0] == '(' && word[len - 1] == ')';
}

int match_A(char* word) {
    size_t len = strlen(word);
    return len > 1 && word[0] == '@'; }

int match_C(char* word) { 
    int sc = 0;
    int ec = 0;
    int semicolon_i = char_index(word, ';'); 
    int len = strlen(word);
    int equals_i = char_index(word, '='); 
    if (!(equals_i < len -1 || semicolon_i < len - 1)) return 0;
    if (equals_i > 0 && semicolon_i > 0 && equals_i < semicolon_i) return 1; 
    else if (equals_i > 0 || semicolon_i > 0) return 1;
    else return 0;
}

int match_com(char* word) {
    for(int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '/') {
            int cindex = i - 1 >= 0 ? i - 1 : i;
            if (word[cindex] == '/' || word[i + 1] == '/') return 1;
            else return 0;
        }  
    }
    return 0;
}

command_type get_command_type(char* line) {
    char* trimmed = trim(line);
    int trimmed_len = strlen(trimmed);
    command_type type;
    if (trimmed_len == 0) type = NO_COMMAND;
    else if (match_com(trimmed)) type = NO_COMMAND;
    else if (match_A(trimmed)) type = A_COMMAND;
    else if (match_L(trimmed)) type = L_COMMAND;   
    else if (match_C(trimmed)) type = C_COMMAND;
    else type = INVALID_COMMAND;
    free(trimmed);
    return type;
}

char* get_symbol(char* str) {
    command_type type = get_command_type(str);
    str = trim(str);
    char* symbol = (char *) malloc(sizeof(char)*strlen(str));  
    int paran_oi = char_index(str, '(');
    int paran_ci = char_index(str, ')');
    if (paran_oi >= 0 && paran_ci >= 0) {
        if (paran_oi >= paran_ci - 1 ) {
            symbol[0] = '\0';
            return symbol;
        }
        str[paran_ci] = '\0';
        strcpy(symbol, str + paran_oi + 1);
        return symbol;
        
    } else if (str[0] == '@' && str[1] != '\0') {
        strcpy(symbol, str + 1);
        return symbol;
    } 
    symbol[0] = '\0';
    free(str);
    return symbol;
}

char* get_dest(char* str) {
    char* dest = (char *) malloc(sizeof(char)*100); 
    str = trim(str);
    int equals_i = char_index(str, '=');
    if (equals_i <= 0) {
        dest[0] = '\0';
        return dest;
    }
    str[equals_i] = '\0';
    strcpy(dest, str);
    free(str); 
    return dest;
}

char* get_jump(char* str) {
    str = trim(str);
    char* jump = (char *) malloc(sizeof(char)*100); 
    int semicolon_i = char_index(str, ';');
    if (semicolon_i != 1) {
        jump[0] = '\0'; 
        return jump;
    }
    strcpy(jump, (str + semicolon_i + 1));
    free(str);
    return jump;
}

char* get_comp(char* str) {
    str = trim(str);
    char* comp = (char *) malloc(sizeof(char)*100); 
    int equals_i = char_index(str, '=');
    int semicolon_i = char_index(str, ';');
    if (equals_i <= 0 && semicolon_i <= 0) {
        comp[0] = '\0';
        return comp;
    }
    int len = strlen(str);
    int end_i = semicolon_i > 0 ? semicolon_i : len; 
    int start_i = equals_i > 0 ? equals_i + 1: 0;
    str[end_i] = '\0'; 
    strcpy(comp, str + start_i );
    free(str);
    return comp;
}
