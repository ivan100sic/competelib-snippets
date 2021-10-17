// Planar line segment

#include <algorithm>
using namespace std;

template<class T>
struct point {
    int x, y;
    bool operator< (const point& b) const { return false; }
    bool operator<= (const point& b) const { return false; }
};

template<class P>
int det(P a, P b, P c) {
    return 0;
}

int sgn(int x) {
    return 0;
}

using ll = long long;

/*snippet-begin*/
template<class T>
struct segment {
    point<T> a, b;

    segment(const point<T>& u, const point<T>& v) : a(u), b(v) {
        if (b < a) swap(a, b);
    }

    template<class R = ll> R len2() { auto x = a-b; return x.template sp<R>(x); }

    template<class R = ll>
    bool contains(const point<T>& c) const {
        return !det(a, b, c) && a <= c && c <= b;
    }

    // Whether insides intersect at a nonzero angle
    template<class R = ll>
    bool intersect_strict(const segment& o) const {
        R p = sgn(det(a, b, o.a)), q = sgn(det(a, b, o.b));
        R r = sgn(det(o.a, o.b, a)), s = sgn(det(o.a, o.b, b));
        return p && q && r && s && p != q && r != s;
    }

    // Whether insides intersect in any way
    template<class R = ll>
    bool intersect(const segment& o) const {
        return intersect_strict(o) || contains(o.a) || contains(o.b)
            || o.contains(a) || o.contains(b);
    }
};
/*snippet-end*/

int main() {
    point<int> a = {0, 0}, b = {1, 1};
    segment<int> s(a, b);
    s.intersect(s);
    s.intersect_strict(s);
}
