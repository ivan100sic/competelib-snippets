// Sparse table

#include <functional>
#include <vector>
using namespace std;

/*snippet-begin*/
template<class T = int, class F = plus<T>>
struct sparse_table {
    vector<vector<T>> d;
    T e;
    F f;

    sparse_table(vector<T> a, T e = T(), F f = F()) : e(e), f(f) {
        d.push_back(a);
        int n = a.size();
        for (int h=1; h*2<=n; h<<=1) {
            int m = a.size() - h;
            vector<T> b(m);
            for (int i=0; i<m; i++)
                b[i] = f(a[i], a[i+h]);
            d.push_back(b);
            swap(a, b);
        }
    }

    T operator() (int l, int r) const {
        if (l >= r) return e;
        int i = 31 - __builtin_clz(r-l);
        return f(d[i][l], d[i][r-(1<<i)]);
    }
};
/*snippet-end*/

template<class T = int, class F = plus<T>>
sparse_table<T, F> make_ds(vector<T> a, T e = T(), F f = F()) {
    return sparse_table<T, F>(a, e, f);
}

int main() {
    auto mn = [](int x, int y) { return min(x, y); };
    auto st = make_ds(vector<int>{1, 2, 3}, 1000, mn);

    return st(0, 2) != 1 || st(1, 3) != 2;
}
