#include <stdio.h>
#include <stdlib.h>
#include "dynlists.h"

void create_and_add_int(dlist *list) {
    
    int *new = malloc(sizeof(int));
    *new = rand()%1001 - 500;
    dlist_append(list, new, "int");
    return;
}

void create_and_add_string(dlist *list) {
    
    int length = rand()%7 + 4;
    char* string = malloc(sizeof(char)*length);
    for(int i=0;i<length-1;i++) {
        string[i] = rand()%26+97;
    }
    string[length-1] = '\0';
    //printf("%s\n", string);
    dlist_append(list, string, "string");
    return;
}

int main() {

    dlist* list = dlist_new();

    dlist_add_printing_function(list, dlist_print_int, "int");
    dlist_add_printing_function(list, dlist_print_string, "string");

    for(int i=0;i<20;i++)
        create_and_add_int(list);
    for(int i=0;i<7;i++)
        create_and_add_string(list);

    dlist_print(list);
    dlist_print_with_func(list, dlist_print_int);
    free(dlist_pop(list,0));
    dlist_print(list);
    dlist_print_with_func(list, dlist_print_int);

    dlist_delete(list);

    return 0;

}