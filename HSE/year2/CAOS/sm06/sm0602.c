//https://prog-cpp.ru/data-dls/ смотрел примеры на данной сайте

#include <stdio.h>
#include <stdlib.h>

struct List 
{
    struct List * parent;
    int value;
    int qty;
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
    x_ptr->qty = 1;
    x_ptr->child = NULL;
    return x_ptr;
}

struct List *find_head(struct List * x) {
    if (x == NULL) {
        return NULL;
    }
    struct List * temp_beg = x;
    while (temp_beg->parent) {
        temp_beg = temp_beg->parent;
    }
    return temp_beg;
}

struct List *find(struct List * x, int v) {

    if (x == NULL) {
        return NULL;
    }

    struct List * temp_beg = x;
    struct List * temp_end = x;

    do {
        if (temp_beg->value == v) {
            return temp_beg;
        }
        temp_beg = temp_beg->parent;
    } while (temp_beg);

    do {
        if (temp_end->value == v) {
            return temp_end;
        }
        temp_end = temp_end->child;
    } while (temp_end);

    return NULL;
}

struct List *add(struct List * x, int num) 
{
    struct List * ptr = find(x, num);
    struct List * head = find_head(x);

    if (ptr == NULL) {
        struct List * temp;
        temp =(struct List*)(malloc(sizeof(struct List)));
        if (temp == NULL) {
            return NULL;
        }
        temp->qty = 1;
        temp->value = num;
        temp->child = head;
        temp->parent = NULL;
        head->parent =  temp;
        return temp;
    } else {
        ptr->qty += 1;
        if (head != ptr) {
            if (ptr->parent != NULL) {
                (ptr->parent)->child = ptr->child;
            }
            if (ptr->child != NULL) {
                (ptr->child)->parent = ptr->parent;
            }
            head->parent = ptr;
            ptr->child = head;
            ptr->parent = NULL;
        }
        return ptr;
    }
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
        printf("%d %d\n", temp_end->value, temp_end->qty);
        temp_end = temp_end->parent;
    } 
}
void delete_list(struct List * x) {
    if (x == NULL) {
        return;
    }
    struct List * temp = find_head(x);
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
