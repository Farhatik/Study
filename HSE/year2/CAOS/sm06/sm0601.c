//https://prog-cpp.ru/data-dls/ смотрел примеры на данной сайте

#include <stdio.h>
#include <stdlib.h>

struct List 
{
    struct List * parent;
    int value;
    struct List * child;

};

struct List *init(int val) 
{
    struct List * x_ptr;
    x_ptr = (struct List*)malloc(sizeof(struct List));
    if (x_ptr == NULL) {
        return NULL;
    }
    x_ptr->parent = NULL;
    x_ptr->value = val;
    x_ptr->child = NULL;
    return x_ptr;
}

struct List *add(struct List * x, int num) {
    struct List * temp;
    temp =(struct List*)(malloc(sizeof(struct List)));
    if (temp == NULL) {
        return NULL;
    }
    temp->value = num;
    temp->parent = x;
    struct List * old_child; 
    old_child =  x->child;
    x->child = temp;
    temp->child = old_child;
    if (old_child != NULL) {
        old_child->parent = temp;
    }
    return temp;
}

void print_rev_list(struct List * x) {
    if (x == NULL) {
        return;
    }
    struct List * temp_end = x;
    while (temp_end->child) {

        temp_end = temp_end->child;
    }
    while(temp_end) {
        printf("%d\n", temp_end->value);
        temp_end = temp_end->parent;
    } 
}
void delete_list(struct List * x) {
    if (x == NULL) {
        return;
    }
    struct List * temp = x;
    while (temp->parent) {
        temp = temp -> parent;
    }
    do {
        struct List * suicide = temp;
        temp = temp->child;
        free(suicide);
    } while (temp);
}

int main() {
    int x;
    int f = 1;
    struct List * my_list = NULL;
    while (scanf("%d", &x) == 1) {
        if (f) {
            my_list = init(x);
            if (my_list == NULL) {
                return 0;
            }
            f = 0;
        } else {
        my_list = add(my_list, x);
        if (my_list == NULL) {
            return 0;
            }   
        }
    }
    print_rev_list(my_list);
    delete_list(my_list);
    return 0;
}
