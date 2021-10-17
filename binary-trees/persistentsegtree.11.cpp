// Persistent segment tree

#include <vector>
#include <functional>
using namespace std;

int midpoint(int l, int r) {
    return (l+r) / 2;
}

/*snippet-begin*/
template<class W, class T = int, class F = plus<T>>
struct persistent_segtree {
    struct node { T v; int l; int r; };
    node dn() { return {e, ~0, ~0}; }
    int cn(int x = 0) { a.emplace_back(a[x]); return a.size() - 1; }

    T e;
    F f;
    W rl, rr;
    vector<node> a;

    persistent_segtree(W rl, W rr, T e = T(), F f = F()) :
        e(e), f(f), rl(rl), rr(rr), a(1, dn()) {}

    template<class L>
    int _au(W p, const T& v, int x, W xl, W xr, L op) {
        x = cn(~x ? x : 0);
        if (xr - xl == 1) {
            op(a[x].v, v);
            return x;
        } else {
            W xm = midpoint(xl, xr);
            bool o = p < xm;
            int t = _au(p, v, o ? a[x].l : a[x].r, o ? xl : xm, o ? xm : xr, op);
            (o ? a[x].l : a[x].r) = t;
            a[x].v = f(~a[x].l ? a[a[x].l].v : e, ~a[x].r ? a[a[x].r].v : e);
            return x;
        }
    }

    int add(int x, W p, const T& v) {
        return _au(p, v, x, rl, rr, [&](T& x, const T& y) { x = f(x, y); });
    }

    int update(int x, W p, const T& v) {
        return _au(p, v, x, rl, rr, [&](T& x, const T& y) { x = y; });
    }

    T get(W l, W r, int x, W xl, W xr) {
        if (!~x || r <= xl || xr <= l)
            return e;
        if (l <= xl && xr <= r)
            return a[x].v;
        W xm = midpoint(xl, xr);
        return f(get(l, r, a[x].l, xl, xm), get(l, r, a[x].r, xm, xr));
    }

    T operator() (int x, W l, W r) { return get(l, r, x, rl, rr); }
};
/*snippet-end*/

int main() {
    persistent_segtree<int> pst(0, 1000);
    pst.add(0, 1, 1);
    pst.update(0, 1, 1);
    pst(0, 0, 1);
}
