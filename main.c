#include <stdio.h>
#include <stdlib.h>
#include "dynlists.h"

void create_and_add_int(dlist *list) {
    
    int *new = malloc(sizeof(int));
    *new = rand()%11 - 0;
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

int* malloc_rand_int() {
    int* random = malloc(sizeof(int));
    *random = rand()%20 + 10000;
    return random;
}

int main() {

    dlist* list = dlist_new();
    //dlist* list_b = dlist_new();

    dlist_add_printing_function(list, dlist_print_int, "int");
    dlist_add_printing_function(list, dlist_print_string, "string");
    dlist_add_compare_function(list, dlist_compare_int, "int");
    dlist_add_compare_function(list, dlist_compare_string, "string");

    for(int i=0;i<10;i++)
        create_and_add_int(list);
    for(int i=0;i<4;i++)
        create_and_add_string(list);
    for(int i=0;i<2;i++)
        create_and_add_int(list);
    for(int i=0;i<8;i++)
        create_and_add_string(list);
    for(int i=0;i<13;i++)
        create_and_add_int(list);
    for(int i=0;i<5;i++)
        create_and_add_string(list);

    //dlist_set_functions(list_b, dlist_get_functions(list));    

    //for(int i=0;i<5;i++)
    //    create_and_add_int(list_b);
    int target = 0;
    int *aux = malloc(sizeof(int));
    //int *tmp = *((int *)dlist_get(list,4));
    *aux = 29;

    //dlist_print_ptrs(list);
    dlist_print(list);
    //dlist_insert(list,-3,malloc_rand_int(),"int");
    //dlist_pop(list, -10);
    //dlist_remove(list, &target, "int");
    //dlist_removeb(list, &target, "int");
    // printf("%d\n", *((int *)dlist_get(list,1))); 
    // free(dlist_get(list,1));
    // dlist_set(list, aux, 1);
    dlist_sort(list);
    dlist_print(list);

    dlist_delete(list);

    return 0;

}