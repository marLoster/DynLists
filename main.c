#include <stdio.h>
#include <stdlib.h>
#include "dynlists.h"

void create_and_add_int(dlist *list) {
    
    int *new = malloc(sizeof(int));
    *new = rand()%501 - 500;
    dlist_add(list, new);
    return;
}

int main() {

    dlist* list = dlist_new();
    for(int i=0;i<20;i++)
        create_and_add_int(list);

    dlist_print_with_func(list, dlist_print_int);

    dlist_delete(list);

    return 0;

}