#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
 
enum { MULT = 1103515245U, INC = 12345U, MOD = 2147483648 };

typedef struct RandomOperations RandomOpertaions;
 
typedef struct RandomGenerator
{
    struct RandomOperations *ops;
    uint32_t temp;
 
} RandomGenerator;
 
 
typedef struct RandomOperations {
    void (*destroy)(RandomGenerator *);
    uint32_t (*next)(RandomGenerator *);
} RandomOperations;
 
void destroy(RandomGenerator *rr) {
    free(rr->ops);
    free(rr);
}
 
uint32_t next(RandomGenerator *rr) {
    rr->temp = (rr->temp * MULT + INC) % MOD;
    return rr->temp;
}
 
 
 
RandomGenerator * random_create(int64_t seed) {
    RandomGenerator *rr = malloc(sizeof(RandomGenerator));
    rr->ops = malloc(sizeof(RandomOperations));
    rr->ops->next =&next;
    rr->ops->destroy = &destroy;
    rr->temp = seed;
    return rr;
}
 
// int main() {
//     RandomGenerator *rr = random_create(1234);
//     for (int64_t j = 0; j < 100; ++j) {
//     printf("%u\n", rr->ops->next(rr));
//     }  
//     rr->ops->destroy(rr);
// }