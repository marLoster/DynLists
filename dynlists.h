#ifndef DYNLISTS
#define DYNLISTS

typedef void (*print_func)(void *);
typedef int (*cmp_func)(const void *,const void *);


typedef struct single_type {
    //Holds info about functions for specific type
    print_func print_function;
    cmp_func cmp_function;
    char type[20];
} type_data;

typedef struct fun_library {
    //Stores library of functions
    type_data *array;
    int size;
} function_library;

typedef struct single_node {
    //node of a list
    struct single_node *prev;
    struct single_node *next;
    char type[20];
    void *data;
} dnode;

typedef struct list_interface {
    //list structure used for almost all operations
    dnode *head;
    dnode *tail;
    int count;
    function_library *functions;
} dlist;

dlist *dlist_new();

void dlist_append(dlist *list,void *data,char *type);
void dlist_clear(dlist *list);
void dlist_delete(dlist *list);

void dlist_print_with_func(dlist *list, print_func printing_function);
void dlist_print(dlist *list);
void dlist_printb(dlist *list);

void dlist_print_int(void *data);
void dlist_print_string(void *data);
int dlist_compare_int(const void *one ,const void *two);
int dlist_compare_string(const void *one ,const void *two);

void *dlist_pop(dlist *list, int index);
void dlist_insert(dlist *list,int index, void *data,char *type);
void dlist_append_list(dlist *dest, dlist *src);
void dlist_reverse(dlist *list);
int dlist_count(dlist *list , void *target, char *type);
int dlist_index(dlist *list , void *target, char *type);
int dlist_indexb(dlist *list , void *target, char *type);
void dlist_remove(dlist *list, void *target, char *type);
void dlist_removeb(dlist *list, void *target, char *type);

void *dlist_get(dlist *list, int index);
void dlist_set(dlist *list, void *data, int index);
int dlist_get_size(dlist *list);

int dlist_get_index(dlist *list, dnode* node);
dnode* dlist_get_node(dlist *list, int index);

void dlist_sort(dlist *list);

int check_position(dnode *head, dnode *tail);
void dlist_quicksort(dlist *list, int left, int right);
void dlist_print_ptrs(dlist *list);
int dlist_partition(dlist *list, int left, int right);
int dlist_general_compare(dlist *list, dnode *a, dnode *b);
void dlist_swap(dlist *list,dnode *a, dnode *b);

void func_clear(function_library *functions);
void func_add_type(function_library *functions, char *type);
void func_add_print(function_library *functions, print_func function, char *type);
void func_add_cmp(function_library *functions, cmp_func function, char *type);
void func_delete(function_library *functions);
function_library *func_create();

void dlist_add_printing_function(dlist *list, print_func function, char *type);
void dlist_add_compare_function(dlist *list, cmp_func function, char *type);
void dlist_clear_functions(dlist *list);
void dlist_set_functions(dlist *list, function_library *functions);
function_library *dlist_get_functions(dlist *list);

#endif