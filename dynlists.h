#ifndef DYNLISTS
#define DYNLISTS

typedef void (*print_func)(void *);
typedef int (*cmp_func)(const void *,const void *);

typedef struct single_type {
    print_func print_function;
    cmp_func cmp_function;
    char type[20];
} type_data;

typedef struct fun_library {
    type_data *array;
    int size;
} function_library;

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
    function_library *functions;
} dlist;


dlist *dlist_new();
void dlist_add(dlist *,void *);
void dlist_append(dlist *,void *,char *);
void dlist_clear(dlist *);
void dlist_delete(dlist *);
void dlist_print_with_func(dlist *, print_func);
void dlist_print_int(void *);
void dlist_print_string(void *);
void dlist_print(dlist *);
void dlist_add_printing_function(dlist *, print_func, char *);
void dlist_add_compare_function(dlist *, cmp_func, char *);
void dlist_clear_functions(dlist *);
void *dlist_pop(dlist *, int);
void func_clear(function_library *);
void func_add_print(function_library *, print_func, char *);
void func_add_cmp(function_library *, cmp_func, char *);
void dlist_set_functions(dlist *, function_library *);
function_library *dlist_get_functions(dlist *);
void func_delete(function_library *);
function_library *func_create();
void func_add_type(function_library *, char *);

#endif