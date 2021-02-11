#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

struct Node 
{
    int value;
    struct Node * left;
    struct Node * right;
    struct Node * parent;
};

struct Node *make_node(int num) 
{
    struct Node * root = malloc(sizeof(struct Node));
    if (root == NULL) {
        return NULL;
    }
    root->parent = NULL;
    root->right = NULL;
    root->left = NULL;
    root->value = num;
    return root;
};

bool is_child(struct Node * x) {
    return (x->left == NULL && x->right == NULL);
}
bool is_root(struct Node * x) {
    return (x->parent == NULL);
}

void add(struct Node * root, int num) {
    if (num < root->value) {
        if (root->left == NULL) {
            struct Node * x = make_node(num);
            if (x == NULL) {
                return;
            }
            root->left = x;
            x->parent = root;
            return;
        } else {
            add(root->left, num);
        }
    } else if (num > root->value) {
        if (root->right == NULL) {
            struct Node * x = make_node(num);
            if (x == NULL) {
                return;
            };
            root->right = x;
            x->parent = root;
            return;
        } else {
            add(root->right, num);
        }
    }
}

void print_tree(struct Node * root)  {
    if (root != NULL) {
        print_tree(root->right);
        printf("%d ", root->value);
        print_tree(root->left);
    }
}

void delete_tree(struct Node * root) {
    if (root != NULL) {
        delete_tree(root->left);
        delete_tree(root->right);
        free(root);
    }
}

int main() {
    int num;
    // bool f_last_tree = true;
    bool f_first_tree = true;
    bool f_first_in_tree = true;
    struct Node * root = NULL;
    while (scanf("%d", &num) == 1) {
        if (num != 0) {
            if (f_first_in_tree) {
                root = make_node(num);
                if (root == NULL) {
                    return 0;
                }
                f_first_in_tree = false;
            } else {
                add(root, num);
            }        
            f_first_tree = false;
        } else {
            print_tree(root);
            printf("0 ");
            delete_tree(root);
            root = NULL;
            f_first_in_tree = true;
            f_first_tree = false;
        }
    }
    if (root != NULL) {
        print_tree(root);
        printf("0");
        delete_tree(root);
        root = NULL;
    }
    if (!f_first_tree) {
        printf("\n");
    }
    return 0;
}