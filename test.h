#include <stdlib.h>
#include <stdio.h>

typedef void (*print_func)(void *);

typedef struct single_node {
    struct single_node *prev;
    struct single_node *next;
    //char type[20];
    void *data;
} dnode;

typedef struct list_interface {
    dnode *head;
    dnode *tail;
    int count;
    //void (*print_functions(void *))[20]
} dlist;

dlist *dlist_new() {
    dlist* aux = malloc(sizeof(dlist));
    aux->count=0;
    aux->head=NULL;
    aux->tail=NULL;
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
