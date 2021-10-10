#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynlists.h"

dlist *dlist_new() {
    dlist* aux = malloc(sizeof(dlist));
    aux->count=0;
    aux->head=NULL;
    aux->tail=NULL;
    aux->print_functions=NULL;
    aux->compare_functions=NULL;
    return aux;
}

void dlist_add(dlist *list,void *data) {
    
    if (!data) {
        return;
    }

    if (!(list->head)) {
        list->head = malloc(sizeof(dnode));
        list->tail = list->head;
        list->count = 1;
        list->head->data=data;
        list->head->next=NULL;
        list->head->prev=NULL;
        return;
    }

    dnode *aux = list->tail;
    list->tail->next = malloc(sizeof(dnode));
    list->tail = list->tail->next;
    list->count += 1;
    list->tail->data=data;
    list->tail->next=NULL;
    list->tail->prev=aux;
    return;
}

void dlist_clear(dlist *list) {
    if (!list ) {
        return;
    }

    dnode *aux;
    while(list->head) {
        aux = list->head->next;
        free(list->head->data);
        free(list->head);
        list->head=aux;
    }
    list->tail=NULL;
    list->count=0;
    return;
}

void dlist_delete(dlist *list) {
    dlist_clear(list);
    free(list);
}

void dlist_print_with_func(dlist *list, print_func printing_function) {
    if (!list) {
        return;
    }

    dnode* iterator=list->head;

    while(iterator) {
        printing_function(iterator->data);
        iterator = iterator->next;
    }

    printf("\n");
    return;
}

void dlist_print_int(void *data) {
    int *integer = (int *) data;
    printf("%d, ",*integer);
    return;
}

void dlist_add_printing_function(dlist *list, print_func fun, char *type) {
    if (!list) {
        return;
    }

    if (!(list->print_functions)) {
        list->print_functions = malloc(sizeof(print_func_and_code));
        list->print_functions[0].function = fun;
        strcpy(list->print_functions[0].type, type);
    }

    //Case with several functions
}
void dlist_add_compare_function(dlist *, cmp_func, char *);
void dlist_clear_printing_functions(dlist *);
void dlist_clear_compare_functions(dlist *);