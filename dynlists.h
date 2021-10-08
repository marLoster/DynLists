#ifndef DYNLISTS
#define DYNLISTS

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

dlist *dlist_new();
void dlist_add(dlist *,void *);
void dlist_clear(dlist *);
void dlist_delete(dlist *);
void dlist_print_with_func(dlist *, print_func);
void dlist_print_int(void *);

#endif