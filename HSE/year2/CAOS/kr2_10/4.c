#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
double ***transpose(double ***arr){
    if (arr == NULL) {
        return NULL;
    }

    int64_t qty_rows_trans = -1;

    for (size_t i = 0; arr[i] != NULL; ++i) {
        for (size_t j = 0; arr[i][j] != NULL; ++j) {
            if (j > qty_rows_trans) {
                qty_rows_trans = j;
            }
        }
    }
    double d = 0;
    double ** ptr_str_d;

    if (qty_rows_trans == -1) {
        double *** arr_trans  = calloc(1, sizeof(ptr_str_d));
        arr_trans[0] = NULL;
        return arr_trans;
    }

    qty_rows_trans++;



    double *** arr_trans = malloc((qty_rows_trans + 1) * sizeof(ptr_str_d));
    double ptr_d;

    size_t * arr_str_size = malloc((qty_rows_trans + 1)* sizeof(qty_rows_trans));


    for (size_t i = 0; arr[i] != NULL; ++i) {
        for (size_t j = 0; arr[i][j] != NULL; ++j) {
                arr_str_size[j] = i;
        }
    }
    

    for (size_t k = 0; k < qty_rows_trans; ++k) {
        double **arr_st = malloc((arr_str_size[k] + 2) * sizeof(ptr_d));
        for (size_t i = 0; i < arr_str_size[k] + 2; ++i) {
            arr_st[i] = NULL;
        }
        arr_trans[k] = arr_st;
    }


    for (size_t i = 0; arr[i] != NULL; ++i) {
        for (size_t j = 0; arr[i][j] != NULL; ++j) {
            double * ptr_d = malloc(sizeof(d));
            *ptr_d = *(arr[i][j]);
            arr_trans[j][i] = ptr_d;
        }
    }


    for (size_t i = 0; i < qty_rows_trans; ++i) {
        for (size_t j = 0; j < arr_str_size[i]; ++j) {
            if (NULL == arr_trans[i][j]) {
                double * ptr_d = malloc(sizeof(d));
                *ptr_d = 0.0;
                arr_trans[i][j] = ptr_d;
            }
        }
    }
    arr_trans[qty_rows_trans] = NULL;
    free(arr_str_size);
    return arr_trans;
}