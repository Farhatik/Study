#include <stdio.h>
#include <stdint.h>

int bitcount(STYPE value){
    UTYPE uvalue = (UTYPE)value;
    int bit_c = 0;   
    while (uvalue > 0) {
        ++bit_c;
        uvalue = uvalue & (uvalue - 1);
    }
    return bit_c;
}
