#include "str_helper.h"

char* trim(char* str) {
    size_t len = strlen(str);
    if (len == 0) return str;
    char* word = (char *) malloc(sizeof(char)*(len+1));
    size_t start = 0;
    size_t hold_start = 0;
    size_t end = len == 0 ? 0 : len - 1;
    size_t hold_end = 0;
    while(start <= end && !(hold_start && hold_end)) {
        if (!hold_start) {
            if (!match_one(str[start], "\n\r \t\a\b\v\f")) {
                hold_start = 1;
            } else {
                start++;
            }
        }
        
        if (!hold_end) {
            if (!match_one(str[end], "\n\r \t\a\b\v\f")) {
                hold_end = 1;
            } else {
                end--;
            }
        }
    }
    size_t i = 0;
    for (i = 0; start + i <= end; i++) {
        word[i] = str[start + i];
    }
    word[i] = '\0';
    return word;
}

int char_index(char* str, char c) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == c) return i;
    }
    return -1;
}

int match_one(char c, char* chars) {
    for (int i = 0; chars[i] != '\0'; i++) {
        if (c == chars[i]) return 1; 
    }
    return 0;
}

/*int chars_index(char* str, char* chars) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (match_one(str[i], chars) return i;
    }
    return -1;
}
*/

char* to_binary_str(int integer, unsigned int len) {
    unsigned int u_integer = (unsigned int) integer;
    char* binary_str = (char*) malloc(sizeof(char)*(len+1));
    for (int i = len - 1; i >= 0; i--) {
        binary_str[i] = u_integer % 2 == 1 ? '1' : '0';  
        u_integer /= 2;
    }
    binary_str[len] = '\0';
    return binary_str;
}

int is_number_str(char* str) {
    for (int i = 0; str[i] != '\0'; i++) {
        if (!(str[i] >= 48 && str[i] <= 57)) return 0;
    }
    return 1;
}
