// Implicit segment tree with lazy updates

#include <vector>
#include <functional>
using namespace std;

int midpoint(int l, int r) {
    return (l+r) / 2;
}

/*snippet-begin*/
template<class T, class U, class F, class G, class H, class W>
struct implicit_segtreelazy {
    struct node { T v; U u; int l; int r; };
    static inline bool is_leaf(W l, W r) { return r-l == 1; }
    node dn() { return {e, eu, ~0, ~0}; }
    int nn() { a.emplace_back(dn()); return a.size() - 1; }

    T e; U eu;
    F f; G g; H h;
    W rl, rr;
    vector<node> a;

    // Add two elements
    // Add two updaters
    // Add an element and an update
    // index range
    // Neutral element
    // Neutral update
    implicit_segtreelazy(F f, G g, H h, W rl, W rr, T e = T(), U eu = U()) :
        e(e), eu(eu), f(f), g(g), h(h), rl(rl), rr(rr), a(1, dn()) {}

    void push(int x, bool leaf) {
        a[x].v = h(a[x].v, a[x].u);
        if (!leaf) {
            if (!~a[x].l) a[x].l = nn();
            if (!~a[x].r) a[x].r = nn();
            a[a[x].l].u = g(a[a[x].l].u, a[x].u);
            a[a[x].r].u = g(a[a[x].r].u, a[x].u);
        }
        a[x].u = eu;
    }

    int update(W l, W r, const U& u, int x, W xl, W xr) {
        if (r <= xl || xr <= l)
            return push(x, is_leaf(xl, xr)), x;
        if (l <= xl && xr <= r)
            return a[x].u = g(a[x].u, u), push(x, is_leaf(xl, xr)), x;
        push(x, is_leaf(xl, xr));
        W xm = midpoint(xl, xr);
        int t;
        t = update(l, r, u, a[x].l, xl, xm), a[x].l = t;
        t = update(l, r, u, a[x].r, xm, xr), a[x].r = t;
        return x;
    }

    T get(W l, W r, int x, W xl, W xr) {
        if (r <= xl || xr <= l)
            return e;
        push(x, is_leaf(xl, xr));
        if (l <= xl && xr <= r)
            return a[x].v;
        W xm = midpoint(xl, xr);
        return f(get(l, r, a[x].l, xl, xm), get(l, r, a[x].r, xm, xr));
    }

    void update(W l, W r, const U& u) { update(l, r, u, 0, rl, rr); }
    T operator() (W l, W r) { return get(l, r, 0, rl, rr); }
};
/*snippet-end*/

template <class T, class U, class F, class G, class H, class W>
implicit_segtreelazy<T, U, F, G, H, W> make_implicit_segtreelazy(F f, G g, H h, W rl, W rr, T e = T(), U eu = U()) {
    return implicit_segtreelazy<T, U, F, G, H, W>(f, g, h, rl, rr, e, eu);
}

int main() {
    auto istl = make_implicit_segtreelazy([](int x, int y) { return max(x, y); }, plus<int>(), plus<int>(), -1000, 1000, -123123123, 0);
    istl.update(0, 0, 1);
    istl(0, 10);
}
