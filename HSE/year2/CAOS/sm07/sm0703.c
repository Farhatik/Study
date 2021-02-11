#include <stdlib.h>
// https://prog-cpp.ru/search-binary/ 

struct BSearchResult
{
    size_t low;
    size_t high;
    int result;
};

struct BSearchResult
bsearch2(
        const void *key,
        const void *base,
        size_t nmemb,
        size_t size,
        int (*compar)(const void *p1, const void *p2, void *user),
        void *user) {
        struct BSearchResult res;
        res.low = 0; res.high = 0; res.result = 0;
        if (nmemb == 0) {
            return res;
        }
        int64_t l = 0;
        int64_t r = nmemb - 1;
        // int f_right = 0;
        // int f_left = 0;
        while (l < r) {
            int64_t mid = (l + r) / 2;
            if (compar(key, base+mid*size, user) == 0) {
                res.result = 1;
                res.high = mid + 1;
                l = mid + 1;
            }
            if (compar(key, base+mid*size, user) > 1) {
                r = mid - 1;
                if (res.result == 0) {
                    res.high = mid - 1;
                }
            }
            if (compar(key, base+mid*size, user) < 1) {
                l = mid + 1;
                if (res.result == 0) {
                    res.high = mid + 1;
                }
            }
        }
        l = 0;
        r = nmemb - 1;
        while (l < r) {
            int64_t mid = (l + r) / 2;
            if (compar(key, base+mid*size, user) == 0) {
                res.result = 1;
                res.low = mid;
                r = mid - 1;
            }
            if (compar(key, base+mid*size, user) > 1) {
                r = mid - 1;
                if (res.result == 0) {
                    res.low = mid - 1;
                }
            }
            if (compar(key, base+mid*size, user) < 1) {
                l = mid + 1;
                if (res.result == 0) {
                    res.low = mid + 1;
                }
            }
        }
        re
        if (res.low == -1) {
            res.high = 0;
            if (res.result == 0) {
                res.high = 0;
            }
        }
        return res;
}




// int main() {
//     return 0;
// }