/* https://www.geeksforgeeks.org/merge-sort/ 
переделана под структуру с сайта*/
#include<stdlib.h> 
#include<stdio.h> 

struct Pair
{
    int key;
    int value;
};


void merge(struct Pair *arr, int64_t l, int64_t m, int64_t r, struct Pair *buf) {
    int64_t i, j, k; 
    int64_t n1 = m - l + 1; 
    int64_t n2 =  r - m; 
    struct Pair *L = buf;
    struct Pair *R = buf + m + 1;
    for (i = 0; i < n1; i++) {
        L[i].key = (arr + l + i)->key; 
        L[i].value = (arr + l + i)->value; 
    } 
    for (j = 0; j < n2; j++) {
        R[j].key = (arr + m + 1 + j)->key; 
        R[j].value = (arr + m + 1+ j)->value;
    }
    i = 0; j = 0; k = l; 
    while (i < n1 && j < n2) 
    { 
        if (L[i].key <= R[j].key) 
        { 
            (arr+k)->key = L[i].key;
            (arr+k)->value = L[i].value;  
            i++; 
        } 
        else
        { 
            (arr+k)->key = R[j].key;
            (arr+k)->value = R[j].value;
            j++; 
        } 
        k++; 
    } 
    while (i < n1) 
    { 
        (arr+k)->key = L[i].key;
        (arr+k)->value = L[i].value;  
        i++; 
        k++; 
    } 
    while (j < n2) 
    { 
        (arr+k)->key = R[j].key; 
        (arr+k)->value = R[j].value; 
        j++; 
        k++; 
    } 
} 


void mergeSort(struct Pair *arr, int64_t l, int64_t r, struct Pair *buf) 
{ 
    if (l < r) 
    { 
        int64_t m = l+(r-l)/2; 
        mergeSort(arr, l, m, buf); 
        mergeSort(arr, m+1, r, buf); 
        merge(arr, l, m, r, buf); 
    } 
} 


void process(struct Pair *data, size_t size) {
    struct Pair *buf = malloc(size * sizeof(*buf));
    if (buf == NULL) return;
    if (size > 1) {
        mergeSort(data, 0, size - 1, buf);
    }
    free(buf);
};