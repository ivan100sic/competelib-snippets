// Link-cut tree (commutative)

#include <vector>
#include <functional>
using namespace std;

/*snippet-begin*/
template<class T = int, class F = plus<T>>
struct link_cut_commutative {
    // Credits: https://codeforces.com/blog/entry/75885
    // 1-based

    struct node {
        T v, s;
        int c[2] = {0, 0}, p = 0, q = 0;
        bool f = false;
    };

    vector<node> a;
    F f;

    link_cut_commutative(int n, T e = T(), F f = F(), T v = T()) : a(n+1), f(f) {
        for (int i=1; i<=n; i++) {
            a[i].v = a[i].s = v;
        }
        a[0].v = a[0].s = e;
    }

    int dir(int x, int y) { return a[x].c[1] == y; }

    void sch(int x, int d, int y) {
        if (x) a[x].c[d] = y, pull(x);
        if (y) a[y].p = x;
    }

    void pull(int x) {
        if (!x) return;
        a[x].s = f(a[a[x].c[0]].s, f(a[x].v, a[a[x].c[1]].s));
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
        swap(a[l].p, a[l].q);
        sch(u, 0, 0);
    }

    void access(int w) {
        for (int v=0, u=w; u; u=a[v=u].q) {
            splay(u);
            splay(v);
            int r = a[u].c[1];
            a[v].q = 0;
            swap(a[r].p, a[r].q);
            sch(u, 1, v);
        }
        splay(w);
    }

    void link(int u, int v) {
        make_root(v);
        a[v].q = u;
    }

    void cut(int u, int v) {
        make_root(u);
        access(u);
        splay(v);
        a[v].q = 0;
    }

    bool connected(int u, int v) {
        if (u == v) return true;
        make_root(u);
        access(v);
        splay(u);
        return a[v].p == u || a[a[v].p].p == u;
    }

    void update(int x, const T& v) {
        make_root(x);
        access(x);
        a[x].v = a[x].s = v;
    }

    T operator()(int u, int v) {
        make_root(u);
        access(v);
        return a[v].s;
    }
};
/*snippet-end*/

int main() {
    link_cut_commutative<int, plus<int>> lcc(3);
    lcc.update(1, 3);
    lcc.update(2, 10);

    if (lcc.connected(1, 2)) return 1;
    lcc.link(1, 2);
    return lcc(1, 2) != 13;
}
