// Fenwick tree

#include <functional>
#include <vector>
using namespace std;

/*snippet-begin*/
template<class T = int, class F = plus<T>>
struct fenwick {
    vector<T> a;
    T e;
    F f;

    fenwick(int n, T e = T(), F f = F()) : a(n, e), e(e), f(f) {}

    void add(int p, const T& v) {
        for (p++; p <= (int)a.size(); p += p & -p)
            a[p-1] = f(a[p-1], v);
    }

    T operator() (int p) const {
        T v = e;
        for (; p; p -= p & -p)
            v = f(v, a[p-1]);
        return v;
    }
};
/*snippet-end*/

int main() {
    fenwick<int, plus<int>> f(10);
    f.add(1, 1);
    f.add(3, 10);
    f.add(5, 100);

    return f(4) != 11;
}
