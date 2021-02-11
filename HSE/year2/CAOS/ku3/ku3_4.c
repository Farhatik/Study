#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#include <stdint.h>
#include <inttypes.h>

struct Elem
{
    struct Elem *next;
    char *str;
};

bool is_number(char * str) {
        bool f_was_digit = false;
        bool f_was_letter = false;

        bool f_was_pl_bef_num = false;
        bool f_was_min_bef_num = false;



        for (char * t_str = str; *t_str != '\0'; t_str++) {
            if (isdigit(*t_str)) {
                f_was_digit = true;
                continue;
            }
            if (!f_was_pl_bef_num && !f_was_min_bef_num && (*t_str == '+')) {
                f_was_pl_bef_num = true;
                continue; 
            }

            if (!f_was_pl_bef_num && !f_was_min_bef_num && (*t_str == '-')) {
                f_was_min_bef_num = true;
                continue; 
            }
            if (!f_was_digit && (*t_str) == ' ') continue;

            if (!isdigit(*t_str)) {
                f_was_letter = true;
                break;
            }
        }
        if (f_was_digit && !f_was_letter) {
            return true;
        }
        return false;
}

struct Elem *dup_elem(struct Elem *head){
    struct Elem * prev = NULL;
    struct Elem * n_head = head;
    
    for (struct Elem * temp = head; temp != NULL; temp = temp->next) {
        if (!is_number(temp->str)) {
            prev = temp;
            continue;
        }
        int64_t x = -1;
        int c = sscanf(temp->str, "%ld", &x);

        if (c != 1) continue;
        if (x >= INT32_MAX || x < (int64_t)INT32_MIN - (int64_t)1) {
            prev = temp;
            continue;
            }
        x++;
        char * s_ptr = malloc(120);
        sprintf(s_ptr, "%ld", x); 

        struct Elem * el_ptr = malloc(sizeof(*el_ptr));

        el_ptr->str = s_ptr;
        el_ptr->next = temp;

        if (prev != NULL) {
            prev->next = el_ptr;
        } else {
            n_head = el_ptr;
        }
        prev = temp;
    }
    return n_head;
}

