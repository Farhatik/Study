
//https://github.com/skuhl/sys-prog-examples/blob/master/simple-examples/qsort_r.c  читал примеры на данном сайте

#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<stdint.h>
 
int compare(const void *t111, const void *t002, void *l) {
    int * ptr1 = (int *) t111;
    int * ptr2 = (int *) t002;
    int y = *ptr2, x = *ptr1;
    const int *mas = l; 
    int a = *(mas + x), b = *(mas+ y);
    if (a != b) {
        if (a > b) {
            return 100;
        } else {
            return -100;
        }
    } else {
        if (x > y) {
            return 100;
        } else {
            return -100;
        }
    }
}


void process(const size_t count, const int *data, int *order) {
    for (int i = 0; i < count; ++i) {
        order[i] = i;
    }
    void * tmp_data =  (void *)data;
    qsort_r(order, count, sizeof(int), compare, tmp_data);
}