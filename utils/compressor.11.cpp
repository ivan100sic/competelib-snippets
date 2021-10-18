// Unique value compressor

#include <vector>
#include <algorithm>

#include <iostream>

using namespace std;

/*snippet-begin*/
template<class T>
struct compressor {
    vector<T*> v;
    T b;
    compressor(T b = T()) : b(b) {}
    void operator+=(T& x) { v.push_back(&x); }
    int operator()() {
        if (v.empty()) return 0;
        sort(v.begin(), v.end(), [](T* x, T* y) { return *x < *y; });
        T p = *v[0];
        *v[0] = b;
        T w = b;
        int q = 1;
        for (size_t i=1; i<v.size(); i++) {
            if (*v[i] != p) ++w, ++q;
            p = *v[i];
            *v[i] = w;
        }
        return q;
    }
};
/*snippet-end*/

int main() {
    vector<int> a = {10, 20, 30, 40, 30, 20, 10};

    compressor<int> c(10);
    for (int i=0; i<7; i++) c += a[i];

    if (c() != 4) return 1;
    return a != vector<int> {10, 11, 12, 13, 12, 11, 10};
}
