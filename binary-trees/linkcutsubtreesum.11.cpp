// Link-cut tree (subtree sum, Abelian groups)

#include <vector>
#include <functional>
using namespace std;

/*snippet-begin*/
template<class T = int, class F = plus<T>, class I = negate<T>>
struct link_cut_subtree_abelian {
    // Credits: https://codeforces.com/blog/entry/75885
    // 1-based

    struct node {
        T v, s, l;
        int c[2] = {0, 0}, p = 0, q = 0;
        bool f = false;
    };

    vector<node> a;
    F f;
    I i;

    link_cut_subtree_abelian(int n, T e = T(), F f = F(), I i = I(), T v = T()) : a(n+1), f(f), i(i) {
        for (int j=1; j<=n; j++) {
            a[j].v = a[j].s = v;
            a[j].l = e;
        }
        a[0].v = a[0].s = a[0].l = e;
    }

    int dir(int x, int y) { return a[x].c[1] == y; }

    void sch(int x, int d, int y) {
        if (x) a[x].c[d] = y, pull(x);
        if (y) a[y].p = x;
    }

    void pull(int x) {
        if (!x) return;
        a[x].s = f(a[a[x].c[0]].s, f(a[x].v, f(a[a[x].c[1]].s, a[x].l)));
    }

    void push(int x) {
        if (!x || !a[x].f) return;
        int& l = a[x].c[0];
        int& r = a[x].c[1];
        a[l].f ^= 1;
        a[r].f ^= 1;
        swap(l, r);
        a[x].f = 0;
    }

    void rotate(int x, int d) {
        int y = a[x].p, z = a[y].p, w = a[x].c[d];
        swap(a[x].q, a[y].q);
        sch(y, !d, w);
        sch(x, d, y);
        sch(z, dir(z, y), x);
    }

    void splay(int x) {
        for (push(x); a[x].p;) {
            int y = a[x].p, z = a[y].p;
            push(z);
            push(y);
            push(x);
            int dx = dir(y, x), dy = dir(z, y);
            if (!z) {
                rotate(x, !dx);
            } else if (dx == dy) {
                rotate(y, !dx);
                rotate(x, !dx);
            } else {
                rotate(x, dy);
                rotate(x, dx);
            }
        }
    }

    void make_root(int u) {
        access(u);
        int l = a[u].c[0];
        a[l].f ^= 1;
        a[u].l = f(a[u].l, a[l].s);
        swap(a[l].p, a[l].q);
        sch(u, 0, 0);
    }

    void access(int w) {
        for (int v=0, u=w; u; u=a[v=u].q) {
            splay(u);
            splay(v);
            int r = a[u].c[1];
            a[u].l = f(a[u].l, a[r].s);
            a[u].l = f(a[u].l, i(a[v].s));
            a[v].q = 0;
            swap(a[r].p, a[r].q);
            sch(u, 1, v);
        }
        splay(w);
    }

    void link(int u, int v) {
        make_root(u);
        access(u);
        make_root(v);
        a[v].q = u;
        a[u].l = f(a[u].l, a[v].s);
        a[u].s = f(a[u].s, a[v].s);
    }

    void cut(int u, int v) {
        make_root(u);
        access(u);
        splay(v);
        a[v].q = 0;
        a[u].l = f(a[u].l, i(a[v].s));
        a[u].s = f(a[u].s, i(a[v].s));
    }

    bool connected(int u, int v) {
        if (u == v) return true;
        make_root(u);
        access(v);
        splay(u);
        return a[v].p == u || a[a[v].p].p == u;
    }

    void update(int x, const T& v) {
        add(x, f(v, i(a[x].v)));
    }

    void add(int x, const T& v) {
        make_root(x);
        access(x);
        a[x].v = f(a[x].v, v);
        a[x].s = f(a[x].s, v);
    }

    T operator()(int v, int p) {
        make_root(p);
        access(p);
        splay(v);
        return a[v].s;
    }
};
/*snippet-end*/

int main() {
    link_cut_subtree_abelian<int, plus<int>, negate<int>> lc(3);
    lc.update(1, 3);
    lc.update(2, 10);
    lc.update(3, 100);
    lc.link(1, 2);
    lc.link(2, 3);
    return lc(2, 1) != 110 || lc(2, 3) != 13;
}
