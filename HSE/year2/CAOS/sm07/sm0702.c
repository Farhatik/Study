//https://github.com/skuhl/sys-prog-examples/blob/master/simple-examples/qsort_r.c  читал примеры на данном сайте

#include<stdio.h>
#include<stdlib.h>

#include<stdint.h>
 
int compare(const void *first, const void *second, void *inform) {
    const int *mas = inform; 
    int x = *((int *) first), y = *(( int *) second);
    int a = mas[x], b = mas[y];
    if (a != b) {
        return a > b;
    } else {
        return x > y;
    }
}
 

void process(const size_t count, const int *data, int *order) {
    for (int i = 0; i < count; ++i) {
        order[i] = i;
    }
    int ex = 0;
    qsort_r(order, count, sizeof(ex), compare, (void *)data);
}
