#include <string.h>
#include "symbol.h"
#include <stdlib.h>

struct symbol_entry* init_symbols() {
    struct symbol_entry* head = (struct symbol_entry*) malloc(sizeof(struct symbol_entry));
    char* name = (char*) malloc(sizeof(char)*3);
    strcpy(name, "SP");
    head->name = name;
    head->address = 0;
    head->next = 0;
    add_entry(head, "LCL",1);
    add_entry(head, "ARG",2);
    add_entry(head, "THIS",3);
    add_entry(head, "THAT",4);
    add_entry(head, "R0",0);
    add_entry(head, "R1",1);
    add_entry(head, "R2",2);
    add_entry(head, "R3",3);
    add_entry(head, "R4",4);
    add_entry(head, "R5",5);
    add_entry(head, "R6",6);
    add_entry(head, "R7",7);
    add_entry(head, "R8",8);
    add_entry(head, "R9",9);
    add_entry(head, "R10",10);
    add_entry(head, "R11",11);
    add_entry(head, "R12",12);
    add_entry(head, "R13",13);
    add_entry(head, "R14",14);
    add_entry(head, "R15",15);
    add_entry(head, "SCREEN",16384);
    add_entry(head, "KBD",24576);
    return head;
}
int contains_symbol(struct symbol_entry* head, char* name) {
    while(head != 0) {
        if (strcmp(head->name, name) == 0) return 1;
        head = head->next;
    }  
    return 0;
}

void add_entry(struct symbol_entry* head, char* name, int address) {
    struct symbol_entry* new = (struct symbol_entry*) malloc(sizeof(struct symbol_entry));
    int len = strlen(name);
    char* new_name = (char*) malloc(sizeof(char)*(len+1));
    strcpy(new_name, name);
    new->name = new_name;
    new->address = address;
    new->next = 0;
    while(head->next != 0) head = head->next;
    head->next = new;
}

int get_address(struct symbol_entry* head, char* name) {
    while(head != 0) {
        if (strcmp(head->name, name) == 0) return head->address;
        head = head->next;
    }
    return -1;
}


