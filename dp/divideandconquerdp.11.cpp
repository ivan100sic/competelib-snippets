// Divide and Conquer DP (Quadrangle Inequality)

#include <vector>
#include <functional>
using namespace std;

using ll = long long;

/*snippet-begin*/
template<class C, class F = less<decltype((*(C*)0)(0, 0))>>
struct divide_and_conquer_dp {
    using T = decltype((*(C*)0)(0, 0));
    C c; F f;

    // Cost function, value comparator (e.g. less for minimization)
    divide_and_conquer_dp(C c, F f = F()) : c(c), f(f) {}

    void q(vector<T>& d, vector<T>& g, vector<int>& p, int l, int r, int a, int b) {
        if (l > r) return;
        int x = (l+r) >> 1;
        int y = a;
        T v = d[a] + c(a, x);
        for (int i=a+1; i<=min(b, x); i++) {
            T w = d[i] + c(i, x);
            if (f(w, v)) v = w, y = i;
        }
        g[x] = v;
        p[x] = y;
        q(d, g, p, l, x-1, a, y);
        q(d, g, p, x+1, r, y, b);
    }

    template<class H>
    void run(int n, int k, H h) {
        vector<T> d(n+1), g(n+1);
        vector<int> p(n+1);
        for (int i=0; i<=n; i++) g[i] = c(0, i);
        h(1, g, p);
        for (int i=2; i<=k; i++) {
            swap(d, g);
            q(d, g, p, 0, n, 0, n);
            h(i, g, p);
        }
    }

    T operator() (int n, int k) {
        T z = T();
        run(n, k, [&](int l, vector<T>& g, vector<int>&) { if (l == k) z = g[n]; });
        return z;
    }

    vector<vector<T>> matrix(int n, int k) {
        vector<vector<T>> a(k+1);
        run(n, k, [&](int l, vector<T>& g, vector<int>&) { a[l] = g; });
        return a;
    }
};
/*snippet-end*/

template<class C, class F = less<decltype((*(C*)0)(0, 0))>>
divide_and_conquer_dp<C, F> make_dp(C c, F f = F()) {
    return divide_and_conquer_dp<C, F>(c, f);
}

int main() {
    auto dp = make_dp([](int x, int y) { return ll(y-x)*(y-x); });

    if (dp(999, 10) != 99801) return 1;
    auto a = dp.matrix(999, 10);
    return a[10][100] != 1000;
}
