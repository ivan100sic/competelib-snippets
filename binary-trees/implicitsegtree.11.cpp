// Implicit segment tree

#include <vector>
#include <random>
#include <map>
#include <functional>
using namespace std;

int midpoint(int l, int r) {
    return (l+r) / 2;
}

/*snippet-begin*/
template<class W, class T = int, class F = plus<T>>
struct implicit_segtree {
    struct node { T v; int l; int r; };
    node dn() { return {e, ~0, ~0}; }
    int nn() { a.emplace_back(dn()); return a.size() - 1; }

    T e;
    F f;
    W rl, rr;
    vector<node> a;

    implicit_segtree(W rl, W rr, T e = T(), F f = F()) :
        e(e), f(f), rl(rl), rr(rr), a(1, dn()) {}

    template<class L>
    int _au(W p, const T& v, int x, W xl, W xr, L op) {
        if (!~x) x = nn();
        if (xr - xl == 1) {
            op(a[x].v, v);
        } else {
            W xm = midpoint(xl, xr);
            bool o = p < xm;
            int t = _au(p, v, o ? a[x].l : a[x].r, o ? xl : xm, o ? xm : xr, op);
            (o ? a[x].l : a[x].r) = t;
            a[x].v = f(~a[x].l ? a[a[x].l].v : e, ~a[x].r ? a[a[x].r].v : e);
        }
        return x;
    }

    void add(W p, const T& v) {
        _au(p, v, 0, rl, rr, [&](T& x, const T& y) { x = f(x, y); });
    }

    void set(W p, const T& v) {
        _au(p, v, 0, rl, rr, [&](T& x, const T& y) { x = y; });
    }

    T get(W l, W r, int x, W xl, W xr) {
        if (!~x || r <= xl || xr <= l)
            return e;
        if (l <= xl && xr <= r)
            return a[x].v;
        W xm = midpoint(xl, xr);
        return f(get(l, r, a[x].l, xl, xm), get(l, r, a[x].r, xm, xr));
    }

    T operator() (W l, W r) { return get(l, r, 0, rl, rr); }
};
/*snippet-end*/

template<class W, class T = int, class F = plus<T>>
implicit_segtree<W, T, F> make_implicit_segtree(W rl, W rr, T e = T(), F f = F()) {
    return implicit_segtree<W, T, F>(rl, rr, e, f);
}

int main() {
    auto ist = make_implicit_segtree(-1000, 1000);
    map<int, int> mp;

    mt19937 eng(1543536);
    using uid = uniform_int_distribution<int>;

    for (int q=0; q<100; q++) {
        int l = uid(-1000, 999)(eng);
        int r = uid(l+1, 1000)(eng);
        int v = uid(-100, 100)(eng);

        if (q % 2) {
            mp[l] += v;
            ist.add(l, v);
        } else {
            int z = 0;
            for (int i=l; i<r; i++) {
                z += mp[i];
            }
            if (z != ist(l, r)) {
                return 1;
            }
        }
    }
}
