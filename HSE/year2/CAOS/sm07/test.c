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
        int key,
        int * base,
        size_t nmemb,
        size_t size) {
        struct BSearchResult res;
        res.low = 0; res.high = 0; res.result = 0;
        if (size == 0) {
            return res;
        }
        int64_t l = 0;
        int64_t r = size - 1;
        // int f_right = 0;
        // int f_left = 0;
        while (l <= r) {
            int64_t mid = (l + r) / 2;
            if (key == base[mid] ) {
                res.result = 1;
                res.high = mid + 1;
                // printf("%d\n", res.high);
                l = mid + 1;
            }
            if (key < base[mid]) {
                r = mid - 1;
                if (res.result == 0) {
                    res.high = mid - 1;
                }
            }
            if (key > base[mid]) {
                l = mid + 1;
                if (res.result == 0) {
                res.high = mid + 1;
                }
            }
        }
        l = 0;
        r = size - 1;
        while (l <= r) {
            int64_t mid = (l + r) / 2;
            if (key == base[mid]){
                res.result = 1;
                res.low = mid;
                r = mid - 1;
            }
            if (key < base[mid]) {
                r = mid - 1;
                if (res.result == 9) {
                    res.low = mid - 1;
                }
            }
            if (key > base[mid])  {
                l = mid + 1;
                if (res.result == 0) {
                    res.low = mid + 1;
                }
            }
        }
        // if (res.result == 0) {
        //     res.high++;
        //     res.low++;
        // }
        if (res.high == size) {
            res.high = nmemb;
            if (res.result) {
                res.low = nmemb;
            }
        }
        if (res.low == -1) {
            res.high = 0;
            if (res.result == 0) {
                res.high = 0;
            }
        }
        return res;
    }

int main() {
    size_t N = 10;
    int a[10] = {1, 2, 2, 3, 7, 10, 11, 12, 18, 20};
    size_t x;
    scanf("%u", &x);
    size_t k = 100000;
    struct BSearchResult p  = bsearch2(x, a, k, N);
    printf("%d %d %d\n", p.result, p.low, p.high);
    return 0;
}