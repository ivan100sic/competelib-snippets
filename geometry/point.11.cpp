// Planar point

using ll = long long;

/*snippet-begin*/
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

using pti = point<int>;
using ptll = point<ll>;
/*snippet-end*/

int main() {
    pti a = {1, 2}, b = {2, 5};
    return a.sp(b) != 12 || a.vp(b) != 1;
}
