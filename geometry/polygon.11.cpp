// Planar polygon

#include <vector>
#include <algorithm>
using namespace std;

using ll = long long;

// taken from point.11.cpp
template<class P, class T = ll>
T det(const P& a, const P& b, const P& c) {
    return (a-b).template vp<T>(a-c);
}

template<class T>
T sgn(T x) {
    return x < 0 ? -1 : !!x;
}

template<class T>
struct point {
    T x, y;
    point operator- (const point& b) const { return {x-b.x, y-b.y}; }
    point& operator-= (const point& b) { x -= b.x; y -= b.y; return *this; }
    bool operator< (const point& b) const { return tie(x, y) < tie(b.x, b.y); }
    bool operator== (const point& b) const { return tie(x, y) == tie(b.x, b.y); }
    bool operator<= (const point& b) const { return tie(x, y) <= tie(b.x, b.y); }
    template<class R = ll> R sp(const point& b) const { return (R)x*b.x + (R)y*b.y; }
    template<class R = ll> R vp(const point& b) const { return (R)x*b.y - (R)y*b.x; }
};
// end taken

/*snippet-begin*/
enum location { Inside, Outside, Boundary };

template<class T = int>
struct polygon {
    vector<point<T>> a;
    template<class R = ll> R dbl_area() const { return abs(sgn_dbl_area()); }

    template<class R = ll> R sgn_dbl_area() const {
        R s = R();
        for (size_t i=1; i+1<a.size(); i++) s += det<point<T>, R>(a[0], a[i], a[i+1]);
        return s;
    }

    template<class R = ll>
    location operator() (const point<T>& p) const {
        int c = 0;
        for (size_t i=0; i<a.size(); i++) {
            size_t j = i+1 == a.size() ? 0 : i+1;
            auto u = a[i]-p, v = a[j]-p;
            if (!u.y && !v.y) {
                if ((u.x <= 0 && 0 <= v.x) || (v.x <= 0 && 0 <= u.x)) {
                    return Boundary;
                } else {
                    continue;
                }
            } else if (u.y && v.y) {
                if (sgn(u.y) == sgn(v.y)) continue;
                auto d = u.template vp<R>(v);
                if (!d) return Boundary;
                if ((d > 0) == (v.y > u.y)) continue;
                c += 2 * sgn(v.y);
            } else {
                if (!u.y) {
                    if (u.x == 0) return Boundary;
                    if (u.x < 0) c += sgn(v.y);
                } else {
                    if (v.x == 0) return Boundary;
                    if (v.x < 0) c -= sgn(u.y);
                }
            }
        }

        return c ? Inside : Outside;
    }
};
/*snippet-end*/

int main() {
    polygon<int> a;
    a.a.push_back({0, 0});
    a.a.push_back({0, 6});
    a.a.push_back({6, 0});

    if (a({4, 2}) != Boundary) return 1;
    if (a({1, 3}) != Inside) return 1;
    if (a({0, 7}) != Outside) return 1;
}
