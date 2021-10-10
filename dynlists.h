#ifndef DYNLISTS
#define DYNLISTS

typedef void (*print_func)(void *);
typedef int (*cmp_func)(const void *,const void *);

typedef struct print_function_and_code {
    print_func function;
    char type[20];
} print_func_and_code;

typedef struct cmp_function_and_type {
    cmp_func function;
    char type[20];
} cmp_func_and_type;

typedef struct single_node {
    struct single_node *prev;
    struct single_node *next;
    char type[20];
    void *data;
} dnode;

typedef struct list_interface {
    dnode *head;
    dnode *tail;
    int count;
    print_func_and_code print_functions;
    int print_count;
    cmp_func_and_type compare_functions;
    int compare_count;
} dlist;


dlist *dlist_new();
void dlist_add(dlist *,void *);
void dlist_clear(dlist *);
void dlist_delete(dlist *);
void dlist_print_with_func(dlist *, print_func);
void dlist_print_int(void *);
void dlist_add_printing_function(dlist *, print_func, char *);
void dlist_add_compare_function(dlist *, cmp_func, char *);
void dlist_clear_printing_functions(dlist *);
void dlist_clear_compare_functions(dlist *);

#endif