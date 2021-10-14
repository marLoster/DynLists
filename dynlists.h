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
int dlist_compare_int(const void *,const void *);
int dlist_compare_string(const void *,const void *);

void dlist_print(dlist *);
void dlist_printb(dlist *);
void dlist_add_printing_function(dlist *, print_func, char *);
void dlist_add_compare_function(dlist *, cmp_func, char *);
void dlist_clear_functions(dlist *);
void dlist_insert(dlist *,int, void *,char *);
void *dlist_pop(dlist *, int);
void dlist_append_list(dlist *, dlist *);
void dlist_reverse(dlist *);
void dlist_remove(dlist *, void *, char *);
void dlist_removeb(dlist *, void *, char *);
void *dlist_get(dlist *, int);
void dlist_set(dlist *list, void *data, int index);
int dlist_count(dlist *, void *, char *);
int dlist_index(dlist *, void *, char *);
int dlist_indexb(dlist *, void *, char *);
void dlist_print_ptrs(dlist *list);

void dlist_sort(dlist *);
void dlist_quicksort(dlist *,int , int);
int dlist_partition(dlist *,int , int);
int dlist_general_compare(dlist *,dnode *, dnode *);
void dlist_swap(dlist *, dnode *, dnode *);
int check_position(dnode *head, dnode *tail);

void func_clear(function_library *);
void func_add_print(function_library *, print_func, char *);
void func_add_cmp(function_library *, cmp_func, char *);
void dlist_set_functions(dlist *, function_library *);
function_library *dlist_get_functions(dlist *);
void func_delete(function_library *);
function_library *func_create();
void func_add_type(function_library *, char *);

#endif