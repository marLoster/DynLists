#include <stdio.h>
#include <stdlib.h>

int main() {
    int *k = malloc(sizeof(int));
    *k=2;

    printf("%d\n", *k);
    return 0;

}