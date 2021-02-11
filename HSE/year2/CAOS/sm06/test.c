#include <stdlib.h>
#include <stdio.h>

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
    x_ptr->parent = NULL;
    x_ptr->value = val;
    x_ptr->child = NULL;
    return x_ptr;
}

struct List *add(struct List * x, int num) {
    struct List * temp;
    temp =(struct List*)(malloc(sizeof(struct List)));
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
    struct List * temp_end = x;
    while (temp_end->child) {
        temp_end = temp_end->child;
    }
    do {
        printf("%d\n", temp_end->value);
        temp_end = temp_end->parent;
    } while (temp_end);
}

void delete_list(struct List * x) {
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
    int val = 5;
    
    struct List * t = init(val);
    
    t = add(t, val);
    print_rev_list(t);
    delete_list(t);
    return 0;
}