#include "str_helper.h"
#include "parser.h"
#include <string.h>

char* dest(char* str) {
    int ia = char_index(str, 'A');  
    int im = char_index(str, 'M');  
    int id = char_index(str, 'D');  
    
    char* dest_bits = (char *) malloc(sizeof(char)*4);
    dest_bits[2] = im >= 0 ? '1' : '0';
    dest_bits[1] = id >= 0 ? '1' : '0';
    dest_bits[0] = ia >= 0 ? '1' : '0';
    dest_bits[3] = '\0';
    return dest_bits;
}

char* comp(char* str) {
    char* comp_bits = (char *) malloc(sizeof(char)*8);
    char* ret;
    ret = "0000000";
    if (strcmp(str, "0") == 0) ret = "0101010";
    if (strcmp(str, "1") == 0) ret = "0111111";
    if (strcmp(str, "-1") == 0) ret = "0111010";
    if (strcmp(str, "D") == 0) ret = "0001100";
    if (strcmp(str, "A") == 0) ret = "0110000";
    if (strcmp(str, "!D") == 0) ret = "0001101";
    if (strcmp(str, "!A") == 0) ret = "0110001";
    if (strcmp(str, "-D") == 0) ret = "0001111";
    if (strcmp(str, "D+1") == 0) ret = "0011111";
    if (strcmp(str, "A+1") == 0) ret = "0110111";
    if (strcmp(str, "D-1") == 0) ret = "0001110";
    if (strcmp(str, "A-1") == 0) ret = "0110010";
    if (strcmp(str, "D+A") == 0) ret = "0000010";
    if (strcmp(str, "D-A") == 0) ret = "0010011";
    if (strcmp(str, "A-D") == 0) ret = "0000111";
    if (strcmp(str, "D&A") == 0) ret = "0000000";
    if (strcmp(str, "D|A") == 0) ret = "0010101";

    if (strcmp(str, "M") == 0) ret = "1110000";
    if (strcmp(str, "!M") == 0) ret = "1110001";
    if (strcmp(str, "-M") == 0) ret = "1110011";
    if (strcmp(str, "M+1") == 0) ret = "1110111";
    if (strcmp(str, "M-1") == 0) ret = "1110010";
    if (strcmp(str, "D+M") == 0) ret = "1000010";
    if (strcmp(str, "D-M") == 0) ret = "1010011";
    if (strcmp(str, "M-D") == 0) ret = "1000111";
    if (strcmp(str, "D&M") == 0) ret = "1000000";
    if (strcmp(str, "D|M") == 0) ret = "1010101";
    strcpy(comp_bits, ret);
    return comp_bits;
}

char* jump(char* str) {
    char* jump_bits = (char *) malloc(sizeof(char)*8);
    char* ret;
    ret = "000";
    if (strcmp(str, "JGT") == 0) ret = "001";
    if (strcmp(str, "JEQ") == 0) ret = "010";
    if (strcmp(str, "JGE") == 0) ret = "011";
    if (strcmp(str, "JLT") == 0) ret = "100";
    if (strcmp(str, "JNE") == 0) ret = "101";
    if (strcmp(str, "JLE") == 0) ret = "110";
    if (strcmp(str, "JMP") == 0) ret = "111";
    strcpy(jump_bits, ret);
    return jump_bits;
}

char* a_ins(char* str) {
    char* symbol = get_symbol(str);
    char* ins_bits = to_binary_str(atoi(str), 16); 
    ins_bits[0] = '0';
    return ins_bits;
}

char* c_ins(char* comp, char* dest, char* jump) {
    char* c_ins = (char *) malloc(sizeof(char)*17);
    c_ins[0] = '1'; 
    c_ins[1] = '1'; 
    c_ins[2] = '1'; 
    c_ins += 3;
    strcpy(c_ins, comp);
    c_ins += 7;
    strcpy(c_ins, dest);
    c_ins += 3;
    strcpy(c_ins, jump); 
    c_ins[16] = '\0';
    return c_ins;
}

