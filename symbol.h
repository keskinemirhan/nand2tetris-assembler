#ifndef SYMBOL_H
#define SYMBOL_H

struct symbol_entry {
    char* name;
    int address;
    struct symbol_entry* next;
};

int contains_symbol(struct symbol_entry* head, char* name);
void add_entry(struct symbol_entry* head, char* name, int address);
int get_address(struct symbol_entry* head, char* name);
struct symbol_entry* init_symbols();

#endif
