// Implicit Li Chao tree

#include <vector>
#include <limits>
using namespace std;

int midpoint(int l, int r) {
    return (l+r) / 2;
}

/*snippet-begin*/
template<class W, class T, bool maximize = false>
struct implicit_lichao {
    struct line {
        T k, b;
        T operator() (W x) const { return k*x + b; }
    };

    struct node { line v; int l; int r; };
    node dn() { return {{0, numeric_limits<T>::max()}, ~0, ~0}; }
    int nn() { a.emplace_back(dn()); return a.size() - 1; }

    W l, r;
    vector<node> a;
    implicit_lichao(W l, W r) : l(l), r(r), a(1, dn()) {}

    int add(line p, int x, W xl, W xr) {
        if (!~x) x = nn();
        if (a[x].v(xl) <= p(xl) && a[x].v(xr) <= p(xr))
            return x;
        if (p(xl) <= a[x].v(xl) && p(xr) <= a[x].v(xr))
            return a[x].v = p, x;
        if (p(xl) < a[x].v(xl))
            swap(p, a[x].v);
        int xm = midpoint(xl, xr);
        a[x].l = add(p, a[x].l, xl, xm);
        a[x].r = add(p, a[x].r, xm+1, xr);
        return x;
    }

    implicit_lichao& operator+= (line p) {
        if (maximize)
            p.k = -p.k, p.b = -p.b;
        add(p, 0, l, r);
        return *this;
    }

    T operator() (W t) const {
        T v = numeric_limits<T>::max();
        int x = 0;
        W xl = l, xr = r;
        while (~x) {
            v = min(v, a[x].v(t));
            W xm = midpoint(xl, xr);
            if (t <= xm) {
                x = a[x].l;
                xr = xm;
            } else {
                x = a[x].r;
                xl = xm + 1;
            }
        }
        return maximize ? -v : v;
    }
};
/*snippet-end*/

int main() {
    implicit_lichao<int, double> ic(-100, 100);
    ic += {1.0, 5.0};
    return ic(10) != 15.0;
}
