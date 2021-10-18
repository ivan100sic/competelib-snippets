// Li Chao segment tree

#include <vector>
#include <limits>
using namespace std;

int midpoint(int x, int y) {
    return (x+y) / 2;
}

/*snippet-begin*/
template<class T, bool maximize = false>
struct lichao {
    struct line {
        T k, b;
        T operator() (T x) const { return k*x + b; }
    };

    int l;
    vector<line> a;

    lichao(int l, int r) : l(l) {
        int maxn = 1;
        while (maxn < r-l)
            maxn <<= 1;
        a.assign(2*maxn, line{0, numeric_limits<T>::max()});
    }

    void add(line p, int x, int xl, int xr) {
        if (a[x](l+xl) <= p(l+xl) && a[x](l+xr) <= p(l+xr))
            return;
        if (p(l+xl) <= a[x](l+xl) && p(l+xr) <= a[x](l+xr)) {
            a[x] = p;
            return;
        }
        if (p(l+xl) < a[x](l+xl))
            swap(p, a[x]);
        int xm = midpoint(xl, xr);
        add(p, 2*x  , xl  , xm);
        add(p, 2*x+1, xm+1, xr);
    }

    lichao& operator+= (line p) {
        if (maximize)
            p.k = -p.k, p.b = -p.b;
        add(p, 1, 0, (a.size()>>1)-1);
        return *this;
    }

    T operator() (int t) const {
        int x = t + (a.size() >> 1) - l;
        T v = a[0].b;
        for (; x; x >>= 1)
            v = min(v, a[x](t));
        return maximize ? -v : v;
    }
};
/*snippet-end*/

int main() {
    lichao<int, false> lc(0, 10);
    lc += {1, 5};
    lc += {-1, 15};

    for (int i=0; i<10; i++) {
        if (lc(i) != min(5+i, 15-i)) {
            return 1;
        }
    }
}
