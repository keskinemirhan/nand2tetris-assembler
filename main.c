#include "parser.h"
#include "code.h"
#include "str_helper.h"
#include "symbol.h"
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv) {
    FILE* raw = fopen(argv[1], "r");
    FILE* out = fopen(argv[2], "w");

    int line_c = 0;
    struct symbol_entry* sym_head = init_symbols();
    while(has_more_commands(raw)) {
        char* line = advance(raw);
        command_type type = get_command_type(line);
        if (type != L_COMMAND) { 
            if (type == A_COMMAND || type == C_COMMAND) line_c++;
            continue;
        }
        char* symbol_str = get_symbol(line);

        int existing_symbol = contains_symbol(sym_head, symbol_str);
        if (existing_symbol) {
            printf("Duplicate Symbol %s", symbol_str);
            return -1;
        }
        if (!existing_symbol) 
            add_entry(sym_head, symbol_str, line_c);
        else free(symbol_str);
        free(line);
    }
    rewind(raw);
    int var_offset = 16;
    while(has_more_commands(raw)) {
        char* line = advance(raw);
        command_type type = get_command_type(line);
        if (type != A_COMMAND) continue;
        char* symbol_str = get_symbol(line);
        if (is_number_str(symbol_str)) continue;
        int existing_symbol = contains_symbol(sym_head, symbol_str);
        if (!existing_symbol) {
            add_entry(sym_head, symbol_str, var_offset++);
        } else free(symbol_str);
        free(line);
    }

    rewind(raw);

    FILE* symres = fopen(".symres", "w");

    while(has_more_commands(raw)) {
        char* line = advance(raw);
        command_type type = get_command_type(line);
        if (type == L_COMMAND) { 
			free(line);
			continue;
		}

		if (type == INVALID_COMMAND || type == NO_COMMAND) {
			free(line);	
			continue;
		}
        if (type != A_COMMAND) {
            fprintf(symres, "%s", line);
            free(line);
            continue;
        } 

        char* symbol_str = get_symbol(line);
        if (is_number_str(symbol_str)) {
            fprintf(symres, "%s", line);
            free(line);
            continue;
        }
        int addr = get_address(sym_head, symbol_str);
        fprintf(symres, "@%d\n", addr);
        free(line);
        free(symbol_str);
    }
    fclose(raw);
    fclose(symres);
    symres = fopen(".symres", "r");
    while(has_more_commands(symres)) {
        char* line = advance(symres);
        command_type type = get_command_type(line);
        if (type == C_COMMAND) {
            char* comp_str = get_comp(line);
            char* dest_str = get_dest(line);
            char* jump_str = get_jump(line);
            char* comp_bits = comp(comp_str);
            char* dest_bits = dest(dest_str);
            char* jump_bits = jump(jump_str);
            fprintf(out, "111%s%s%s\n",comp_bits,dest_bits,jump_bits);  
            free(comp_str);
            free(dest_str);
            free(jump_str);
            free(comp_bits);
            free(dest_bits);
            free(jump_bits);
        } else if (type == A_COMMAND) {
            char* symbol_str = get_symbol(line);
            fprintf(out, "%s\n", a_ins(symbol_str));
            free(symbol_str);
        }
        free(line);
    }
    fclose(out);
    fclose(symres);
    return 1;    
}


