#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "dynlists.h"

dlist *dlist_new() {

    dlist* aux = malloc(sizeof(dlist));

    if (!aux) {
        return NULL;
    }

    aux->count=0;
    aux->head=NULL;
    aux->tail=NULL;
    aux->functions=func_create();
    return aux;

}

void dlist_append(dlist *list,void *data,char *type) {
        
    if (!list) {
        return;
    }

    if (!(list->head)) {
        list->head = malloc(sizeof(dnode));
        
        if (list->head==NULL) {
            return;
        }

        list->tail = list->head;
        list->count = 1;
        list->head->data=data;
        strcpy(list->head->type,type);
        list->head->next=NULL;
        list->head->prev=NULL;
        return;
    }

    dnode *aux = list->tail;
    list->tail->next = malloc(sizeof(dnode));

    if (list->tail->next==NULL) {
        return;
    }

    list->tail = list->tail->next;
    list->count += 1;
    list->tail->data=data;
    strcpy(list->tail->type,type);
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

    list->head=NULL;
    list->tail=NULL;
    list->count=0;
    return;
}

void dlist_delete(dlist *list) {

    dlist_clear(list);
    func_delete(list->functions);
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
        if (iterator) {
            printf(", ");
        }
    }

    printf("\n");
    return;
}

void dlist_print(dlist *list) {

    if (!list) {
        return;
    }

    dnode* iterator=list->head;

    while(iterator) {

        for(int i=0;i<list->functions->size;i++) {
            if (!strcmp(iterator->type,list->functions->array[i].type)) {
                list->functions->array[i].print_function(iterator->data);
                break;
            }
        }

        iterator = iterator->next;
        if (iterator) {
            printf(", ");
        }
    }

    printf("\n");
    return;
}

void dlist_printb(dlist *list) {

    if (!list) {
        return;
    }

    dnode* iterator=list->tail;

    while(iterator) {

        for(int i=0;i<list->functions->size;i++) {
            if (!strcmp(iterator->type,list->functions->array[i].type)) {
                list->functions->array[i].print_function(iterator->data);
                break;
            }
        }

        iterator = iterator->prev;
        if (iterator) {
            printf(", ");
        }
    }

    printf("\n");
    return;
}

void dlist_print_int(void *data) {

    int *integer = (int *) data;
    printf("%d",*integer);
    return;

}

void dlist_print_string(void *data) {

    char *string = (char *) data;
    printf("%s", string);
    return;

}

int dlist_compare_int(const void *one ,const void *two) {

    const int *a = (const int *)one;
    const int *b = (const int *)two;

    return *a - *b;

}

int dlist_compare_string(const void *one ,const void *two) {

    const char *a = (const char *)one;
    const char *b = (const char *)two;

    return strcmp(a,b);

}

void *dlist_pop(dlist *list, int index) {

    if (!list) {
        return NULL;
    }

    if (list->count-1<index) {
        return NULL;
    }

    if (index<0) {
        index = list->count + index;
    }

    if (index<0) {
        return NULL;
    }

    void *res;
    dnode *aux;

    if (index==0) {
        if (list->head==list->tail) {
            res = list->head->data;
            free(list->head);
            list->head=NULL;
            list->tail=NULL;
            list->count=0;
            return res;
        }
        else {
            aux = list->head->next;
            res = list->head->data;
            free(list->head);
            list->head = aux;
            list->head->prev = NULL;
            list->count -= 1;
            return res;
        }
    }

    if (index==list->count-1) {
        res = list->tail->data;
        aux = list->tail->prev;
        free(list->tail);
        list->tail = aux;
        list->tail->next=NULL;
        list->count -= 1;
        return res;
    }

    aux = dlist_get_node(list,index);

    if (!aux) {
        puts("error: cannot get node");
        return NULL;
    }

    aux->next->prev = aux->prev;
    aux->prev->next = aux->next;
    res = aux->data;
    free(aux);
    list->count -= 1;
    return res;
}

void dlist_insert(dlist *list,int index, void *data,char *type) {

    if (!list) {
        return;
    }

    if (index>=list->count) {
        dlist_append(list, data, type);
        return;
    }

    if (index<0) {
        index = list->count + index;
    }

    dnode *aux;
    
    if (index<=0) {
        aux = malloc(sizeof(dnode));

        if (!aux) {
            return;
        }

        aux->data=data;
        aux->next=list->head;
        aux->prev=NULL;
        strcpy(aux->type,type);
        list->count+=1;
        list->head=aux;
        return;
    }


    dnode *node = dlist_get_node(list,index);

    if (!node) {
        puts("error cannot get node");
        return;
    }
    
    aux = malloc(sizeof(dnode));

    if (!aux) {
        return;
    }

    aux->data=data;
    aux->next=node;
    aux->prev=node->prev;
    strcpy(aux->type,type);
    node->prev=aux;
    aux->prev->next=aux;
    list->count+=1;

    return;
}

void dlist_append_list(dlist *dest, dlist *src) {

    if (!(dest && src)) {
        return;
    }

    if (src->head==NULL) {
        return;
    }
    
    if(dest->head == NULL) {
        dest->head=src->head;
        dest->tail=src->tail;
        dest->count=src->count;
        src->head=NULL;
        src->tail=NULL;
        src->count=0;        
        return;
    }

    src->head->prev=dest->tail;
    dest->tail->next=src->head;
    dest->count+=src->count;
    dest->tail=src->tail;
    src->head=NULL;
    src->tail=NULL;
    src->count=0; 
    return;
}

void dlist_reverse(dlist *list) {

    if (list==NULL || list->count<2) {
        return;
    }

    dnode *iterator = list->head;
    dnode *aux;

    while(iterator) {
        aux = iterator->prev;
        iterator->prev = iterator->next;
        iterator->next = aux;
        iterator = iterator->prev;
    }

    aux = list->head;
    list->head = list->tail;
    list->tail=aux;

    return;
}

int dlist_count(dlist *list , void *target, char *type) {

    if (!list) {
        return -1;
    }

    cmp_func compare_function=NULL;

    for(int i=0;i<list->functions->size;i++) {
        if (strcmp(list->functions->array[i].type,type)==0) {
            compare_function = list->functions->array[i].cmp_function;
            break;
        }
    }

    if (!compare_function) {
        return -1;
    }

    dnode *iterator=list->head;
    int count=0;

    while(iterator) {
        if (strcmp(iterator->type,type)==0) {
            if (compare_function(iterator->data,target)==0) {
                count+=1;
            }
        }
        iterator=iterator->next;
    }

    return count;
}

int dlist_index(dlist *list , void *target, char *type) {
    if (!list) {
        return -1;
    }

    cmp_func compare_function=NULL;

    for(int i=0;i<list->functions->size;i++) {
        if (strcmp(list->functions->array[i].type,type)==0) {
            compare_function = list->functions->array[i].cmp_function;
            break;
        }
    }

    if (!compare_function) {
        return -1;
    }

    dnode *iterator=list->head;
    int index = 0;

    while(iterator) {
        if (strcmp(iterator->type,type)==0) {
            if (compare_function(iterator->data,target)==0) {
                return index;
            }
        }
        iterator=iterator->next;
        index++;
    }

    return -1;    
}

int dlist_indexb(dlist *list , void *target, char *type) {
    if (!list) {
        return -1;
    }

    cmp_func compare_function=NULL;

    for(int i=0;i<list->functions->size;i++) {
        if (strcmp(list->functions->array[i].type,type)==0) {
            compare_function = list->functions->array[i].cmp_function;
            break;
        }
    }

    if (!compare_function) {
        return -1;
    }

    dnode *iterator=list->tail;
    int index = list->count-1;

    while(iterator) {
        if (strcmp(iterator->type,type)==0) {
            if (compare_function(iterator->data,target)==0) {
                return index;
            }
        }
        iterator=iterator->prev;
        index--;
    }

    return -1;    
}

void dlist_remove(dlist *list, void *target, char *type) {

    if (!list) {
        return;
    }

    int index = dlist_index(list,target,type);
    if (index<0) {
        return;
    }
    free(dlist_pop(list,index));
    return;
}
void dlist_removeb(dlist *list, void *target, char *type) {

    if (!list) {
        return;
    }

    int index = dlist_indexb(list,target,type);
    if (index<0) {
        return;
    }
    free(dlist_pop(list,index));
    return;
}

void *dlist_get(dlist *list, int index) {
    
    if (!list) {
        return NULL;
    }
    
    dnode* node = dlist_get_node(list,index);

    if (!node) {
        return NULL;
    }

    return node->data;
}

void dlist_set(dlist *list, void *data, int index) {
    if (!list) {
        return;
    }

    dnode* node = dlist_get_node(list,index);

    if (!node) {
        return;
    }

    node->data=data;
    return;
}

int dlist_get_size(dlist *list) {
    
    if (!list) {
        return -1;
    }
    
    return list->count;
}

int dlist_get_index(dlist *list, dnode* node) {
    
    if (!list || !node) {
        return -1;
    }

    int index = 0;
    dnode *iterator = list->head; 

    while(iterator!=node && iterator) {
        iterator=iterator->next;
        index++;
    }

    return index;
}

dnode* dlist_get_node(dlist *list, int index) {
    
    if (!list) {
        return NULL;
    }

    int count=0;
    dnode *iterator = list->head;

    while(count!=index && iterator) {
        iterator=iterator->next;
        count++;
    }

    return iterator;

}

void dlist_sort(dlist *list) {
    if (!list || list->head==NULL || list->count==1) {
        return;
    }

    dlist_quicksort(list, dlist_get_index(list,list->head),dlist_get_index(list,list->tail));
    return;

}

int check_position(dnode *head, dnode *tail) {
    dnode *iterator = head;
    while(iterator) {
        iterator=iterator->next;
        if (iterator==tail) {
            return 1;
        }
    }

    return 0;
}

void dlist_quicksort(dlist *list, int left, int right) {
    if(left<right) {
        int border = dlist_partition(list, left,right);
        dlist_quicksort(list, left,border);
        dlist_quicksort(list, border+1,right);
    }
    return;
}

void dlist_print_ptrs(dlist *list) {
    
    if (!list) {
        return;
    }

    dnode *iterator = list->head;

    while(iterator) {
        printf("%p: ^%p^ v%pv\n", iterator, iterator->prev, iterator->next);
        iterator=iterator->next;
    }
    return;
}

int dlist_partition(dlist *list, int left, int right) {

    dnode left_start;
    left_start.next = dlist_get_node(list,left);
    dnode *left_iterator = &left_start;
    
    dnode right_start;
    right_start.prev = dlist_get_node(list,right);
    dnode *right_iterator = &right_start;

    dnode *head = dlist_get_node(list,left);

    if (left_start.next == NULL || right_start.prev == NULL || head == NULL) {
        puts("error: cannot get node");
        return left;
    }

    dnode *aux;

    while(1) {
        do {
            if (right_iterator)
            right_iterator=right_iterator->prev;
        } while(dlist_general_compare(list, right_iterator,head)>0 && right_iterator);

        do {
            if (left_iterator)
            left_iterator = left_iterator->next;
        } while(dlist_general_compare(list, left_iterator,head)<0 && left_iterator);

        if (check_position(left_iterator,right_iterator)) {
            dlist_swap(list, left_iterator,right_iterator);
            aux = right_iterator;
            right_iterator = left_iterator;
            left_iterator = aux;
        }
        else {
            return dlist_get_index(list,right_iterator);
        }
    }

}

int dlist_general_compare(dlist *list, dnode *a, dnode *b) {
    
    if (strcmp(a->type,b->type)) {
        return strcmp(a->type,b->type);
    }

    cmp_func compare_function=NULL;

    for(int i=0;i<list->functions->size;i++) {
        if (strcmp(list->functions->array[i].type,a->type)==0) {
            compare_function = list->functions->array[i].cmp_function;
            break;
        }
    }

    if (!compare_function) {
        return 0;
    }

    return compare_function(a->data,b->data);

}

void dlist_swap(dlist *list,dnode *a, dnode *b) {
    
    //a must be before b if you want this to work!
    
    if (!a || !b) {
        return;
    }

    if (a->next==b) {
        
        if (a->prev) {
            a->prev->next=b;
        }
        else {
            list->head=b;
        }

        if (b->next) {
            b->next->prev=a;
        }
        else {
            list->tail=a;
        }

        a->next=b->next;
        b->next=a;
        b->prev=a->prev;
        a->prev=b;

        return;
    }

    a->next->prev=b;

    if (a->prev) {
        a->prev->next=b;
    }
    else {
        list->head=b;
    }

    b->prev->next=a;

    if (b->next) {
        b->next->prev=a;
    }
    else {
        list->tail=a;
    }

    dnode *aux;

    aux = b->prev;
    b->prev = a->prev;
    a->prev = aux;

    aux = b->next;
    b->next = a->next;
    a->next = aux;

    return;
}



void func_clear(function_library *functions) {
    functions->size=0;
    free(functions->array);
    functions->array=NULL;
} 

void func_add_type(function_library *functions, char *type) {
    
    if (!functions) {
        return;
    }

    if (functions->size==0) {
        functions->array=malloc(sizeof(type_data));

        if (functions->array==NULL) {
            return;
        }

        functions->array[0].cmp_function=NULL;
        functions->array[0].print_function=NULL;
        strcpy(functions->array[0].type,type);
        functions->size=1;
        return;
    }

    else {
        type_data *aux = realloc(functions->array,(functions->size+1)*sizeof(type_data));
        
        if (!aux) {
            return;
        }
        
        functions->size+=1;
        functions->array=aux;
        functions->array[functions->size-1].cmp_function=NULL;
        functions->array[functions->size-1].print_function=NULL;
        strcpy(functions->array[functions->size-1].type,type);
    }

}

void func_add_print(function_library *functions, print_func function, char *type) {
    if (!functions) {
        return;
    }

    for(int i=0;i<functions->size;i++) {
        if (!strcmp(functions->array[i].type,type)) {
            functions->array[i].print_function = function;
            return;
        }
    }

    func_add_type(functions, type);

    for(int i=0;i<functions->size;i++) {
        if (!strcmp(functions->array[i].type,type)) {
            functions->array[i].print_function = function;
            return;
        }
    }

}

void func_add_cmp(function_library *functions, cmp_func function, char *type) {
    if (!functions) {
        return;
    }

    for(int i=0;i<functions->size;i++) {
        if (!strcmp(functions->array[i].type,type)) {
            functions->array[i].cmp_function = function;
            return;
        }
    }

    func_add_type(functions, type);

    for(int i=0;i<functions->size;i++) {
        if (!strcmp(functions->array[i].type,type)) {
            functions->array[i].cmp_function = function;
            return;
        }
    }

}

void func_delete(function_library *functions) {
    func_clear(functions);
    free(functions);
}

function_library *func_create() {
    function_library *res = malloc(sizeof(function_library));

    if (!res) {
        return NULL;
    }

    res->array=NULL;
    res->size=0;
    return res;
}

void dlist_add_printing_function(dlist *list, print_func function, char *type) {
    func_add_print(list->functions, function, type);
    return;
}

void dlist_add_compare_function(dlist *list, cmp_func function, char *type) {
    func_add_cmp(list->functions, function, type);
    return;
}

void dlist_clear_functions(dlist *list) {
    func_clear(list->functions);
    return;
}

void dlist_set_functions(dlist *list, function_library *functions) {
    list->functions=functions;
    return;
}

function_library *dlist_get_functions(dlist *list) {
    return list->functions;
}