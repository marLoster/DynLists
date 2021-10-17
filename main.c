#include <stdio.h>
#include <stdlib.h>
#include "dynlists.h"

typedef struct test_structure {
    int x;
    int y;
} test_struct;

void struct_print(void *ptr) {
    test_struct *structure = (test_struct *)ptr;
    printf("(%d, %d)",structure->x,structure->y);
    return;
}

int struct_compare(const void *one, const void *two) {
    test_struct *a = (test_struct *) one;
    test_struct *b = (test_struct *) two;

    if(a->x - b->x) {
        return a->x - b->x;
    }
    return a->y - b->y;
}

void create_and_add_int(dlist *list) {
    
    int *new = malloc(sizeof(int));
    *new = rand()%201 - 100;
    dlist_append(list, new, "int");
    return;
}

void create_and_add_structure(dlist *list) {
    
    test_struct *structure = malloc(sizeof(test_struct));
    structure->x = rand()%21 - 10;
    structure->y = rand()%21 - 10;
    dlist_append(list, structure, "structure");
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

    //append test

    for(int i=0;i<4;i++)    
        create_and_add_int(list);

    //print with func test
    puts("Basic test");
    dlist_print_with_func(list,dlist_print_int);

    //clear test
    dlist_clear(list);
    dlist_print_with_func(list,dlist_print_int);;
    
    //dlist function library test
    dlist_add_printing_function(list, dlist_print_int, "int");
    dlist_add_printing_function(list, dlist_print_string, "string");
    dlist_add_printing_function(list, struct_print, "structure");
    dlist_add_compare_function(list, dlist_compare_int, "int");
    dlist_add_compare_function(list, dlist_compare_string, "string");
    dlist_add_compare_function(list, struct_compare, "structure");
    

    //fill up the list
    for(int i=0;i<5;i++)
        create_and_add_int(list);
    for(int i=0;i<4;i++)
        create_and_add_string(list);
    for(int i=0;i<2;i++)
        create_and_add_int(list);
    for(int i=0;i<4;i++)
        create_and_add_structure(list);
    for(int i=0;i<3;i++)
        create_and_add_string(list);
    for(int i=0;i<2;i++)
        create_and_add_int(list);
    for(int i=0;i<5;i++)
        create_and_add_string(list);
    for(int i=0;i<7;i++)
        create_and_add_structure(list);


    //print test
    puts("Printing test:");
    dlist_print(list);
    puts("Printing backwards test:");
    dlist_printb(list);

    //pop and get_size test
    puts("pop test - pop 0 then 8 then last element:");
    free(dlist_pop(list, 0));
    free(dlist_pop(list,8));
    free(dlist_pop(list,dlist_get_size(list)-1));
    dlist_print(list);

    //insert test
    puts("insert random int at 10:");
    dlist_insert(list,10,malloc_rand_int(),"int");
    dlist_print(list);

    //append list test
    puts("append list test:");
    dlist *other_list = dlist_new();
    for(int i=0;i<10;i++)
        create_and_add_int(other_list);
    dlist_append_list(list,other_list);
    dlist_delete(other_list);
    dlist_print(list);

    //reverse test
    puts("reverse test:");
    dlist_reverse(list);
    dlist_print(list);

    //count test
    int aux = 1;
    printf("there are %d zeros in the list\n",dlist_count(list, &aux, "int"));
    printf("first occurnece of zero: %d\n", dlist_index(list, &aux, "int"));
    printf("last occurence of zero: %d\n", dlist_indexb(list, &aux, "int"));
    dlist_remove(list, &aux, "int");
    dlist_removeb(list, &aux, "int");    

    //get_and set_test
    puts("get and set test = get 0 and set 1 to random int:");
    int *aux_ = dlist_get(list,0);
    printf("%d\n", *aux_);
    dlist_set(list,malloc_rand_int(),1);
    dlist_print(list);

    //sort test
    puts("sort test:");
    dlist_sort(list);
    dlist_print(list);

    //delete test
    dlist_delete(list);

    return 0;

}