// Mexer (Small numbers)

#include <cstring>
using ull = unsigned long long;

/*snippet-begin*/
template<int n>
struct mexer_small {
    ull a[n];

    mexer_small() { memset(a, 0, sizeof(a)); }
    void operator+= (int x) { a[x >> 6] |= 1ull << (x & 63); }
    int operator() () const {
        for (int i=0; i<n; i++) if (a[i] != ~0ull) return (i << 6) + __builtin_ctzll(~a[i]);
        return -1;
    }
};
/*snippet-end*/

int main() {
    mexer_small<4> ms;

    for (int i=0; i<200; i++) {
        if (i != 100) {
            ms += i;
        }
    }

    return ms() != 100;
}
