#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <inttypes.h>
#include <string.h>

struct Elem
{
    struct Elem *next;
    char *str;
};

struct Elem *process_3(struct Elem *head, char *str, int precount) {
    int before_el = 0;
    struct Elem * x = head;
    for (struct Elem * temp = head; temp != NULL; temp = temp->next) {
        int temp_res =  strcmp(str, temp->str);
        if (temp_res > 0) {
            // printf("%s\n",temp->str);
            before_el++;
            x = NULL;
            continue;
        } else if (temp_res == 0) {
            return head;
        } else {
            x = temp;
            break;
        }
    }
    struct Elem * new_head = malloc(sizeof(*new_head));
    new_head->next = x;
    char * str_head = (char *)malloc(strlen(str) + 1);
    if (str != NULL && str_head != NULL) {
        strcpy(str_head, str);
    } else {
        str_head = NULL;
    }
    new_head->str = str_head;
    if (precount >= before_el) {
        struct Elem * temp = head;
        for (int i = 0; i < before_el; ++i) {
            struct Elem * temp_next = temp->next;
            free(temp->str);
            free(temp);
            temp = temp_next;
        }
        return new_head;
    }
    struct Elem * new_tail = head;
    for (int i = 0; i < before_el - precount - 1; ++i) {
        new_tail = new_tail->next;
    }
    //printf("%d\n", before_el);
    struct Elem * temp = new_tail->next;
    if (temp != NULL) {
        for (int i = 0; i < precount; ++i) {
        struct Elem * temp_next = temp->next;
        //printf("%s\n", temp->str);
        free(temp->str);
        free(temp);
        temp = temp_next;
        }
    }
    new_head->next = temp;
    new_tail->next = new_head;
    return head;
}