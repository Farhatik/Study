#include <stdio.h>
#include <stdlib.h>

struct Pair
{
    int key;
    int value;
};


void process(struct Pair *p, size_t size) 
{
    int compare(const void *a, const void * b) {
        int k1 = ((struct Pair *)a)->key;
        int k2 = ((struct Pair *)b)->key;
        if (k1 <= k2) {
            return -1;
        } else {
            return 1;
        }
    }
    qsort(p, size, 8, compare);
}
