// Divide and Conquer DP (Quadrangle Inequality)

#include <vector>
#include <functional>
using namespace std;

/*snippet-begin*/
template<class T, class C, class F = less<T>>
struct divide_and_conquer_dp {
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
        run(n, k, [&](int l, vector<T>& g, vector<T>& p) { if (l == k) z = g[n]; });
        return z;
    }
};
/*snippet-end*/

template<class T, class C, class F = less<T>>
divide_and_conquer_dp<T, C, F> make_dp(C c, F f = F()) {
    return divide_and_conquer_dp<T, C, F>(c, f);
}

int main() {
    auto dp = make_dp<int>([](int x, int y) { return (y-x)*(y-x); });

    return dp(5, 3) != 9;
}
