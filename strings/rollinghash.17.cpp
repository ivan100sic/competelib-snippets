// Rolling hash

#include <chrono>
#include <vector>
using namespace std;

using ll = long long;

// taken from modint.11
template<int m>
struct modint {
    unsigned x;

    modint() : x(0) {}
    modint(long long arg) : x((arg %= m) < 0 ? arg + m : arg) {}

    modint operator+ (const modint& b) const {
        auto t = *this; t.x = (t.x += b.x) >= m ? t.x-m : t.x; return t;
    }

    modint operator- (const modint& b) const {
        auto t = *this; t.x = (t.x += m-b.x) >= m ? t.x-m : t.x; return t;
    }

    modint operator* (const modint& b) const {
        auto t = *this; t.x = ll(t.x) * b.x % m; return t;
    }

    modint operator/ (const modint& b) const {
        return *this * b.inv();
    }

    template<class T> modint operator^ (T n) const {
        modint t;
        if (n == 0) return t.x = 1, t;
        if (n == 1) return t.x = x, t;
        t = *this ^ (n >> 1); t *= t;
        return n & 1 ? *this * t : t;
    }

    modint& operator+= (const modint& b) { return *this = *this + b; }
    modint& operator-= (const modint& b) { return *this = *this - b; }
    modint& operator*= (const modint& b) { return *this = *this * b; }
    modint& operator/= (const modint& b) { return *this = *this / b; }
    modint& operator++ () { if (++x == m) x = 0; return *this; }
    modint& operator-- () { if (x-- == 0) x = m-1; return *this; }
    modint operator++ (int) { modint tmp = *this; ++*this; return tmp; }
    modint operator-- (int) { modint tmp = *this; --*this; return tmp; }
    bool operator== (const modint& other) const { return x == other.x; }
    bool operator!= (const modint& other) const { return x != other.x; }
    int operator() () const { return x; }
    template<class T> modint operator^= (T n) { return *this = *this ^ n; }
    modint inv() const { return *this ^ (m-2); }
};
// end taken

/*snippet-begin*/
template<int mod>
struct rolling_hash {
    using T = modint<mod>;

    static inline T base;
    static inline vector<T> pws;

    static T pw(int x) {
        if (pws.empty()) {
            base = chrono::high_resolution_clock::now().time_since_epoch().count();
            pws = {1};
        }

        while (x >= (int)pws.size()) pws.push_back(pws.back() * base);
        return pws[x];
    }

    int l;
    T h;

    rolling_hash() : l(0), h(0) {}

    template<class X>
    rolling_hash(X x) : l(1), h(x) {}

    rolling_hash(int&& l, T&& h) : l(l), h(h) {}

    rolling_hash operator+ (const rolling_hash& b) const {
        return {l + b.l, h * pw(b.l) + b.h};
    }

    rolling_hash operator- (const rolling_hash& b) const {
        return {l - b.l, h - pw(l - b.l) * b.h};
    }

    bool operator< (const rolling_hash& b) const { return h() < b.h(); };
    bool operator> (const rolling_hash& b) const { return h() > b.h(); };
    bool operator== (const rolling_hash& b) const { return h == b.h; };
    bool operator!= (const rolling_hash& b) const { return h != b.h; };
    bool operator<= (const rolling_hash& b) const { return h() <= b.h(); };
    bool operator>= (const rolling_hash& b) const { return h() >= b.h(); };
};
// Some primes: 1921500998 1922211060 1819854627 1849026543
/*snippet-end*/

int main() {
    const int P = 1921500998;
    rolling_hash<P> a(1);
    rolling_hash<P> b(2);
    rolling_hash<P> c(3);

    if (a < b && b < c && c < a) return 1;
    if (a > b && b > c && c > a) return 1;
    if (a >= b && b >= c && c >= a) return 1;
    if (a <= b && b <= c && c <= a) return 1;

    return (a + (b + c)) != ((a + b) + c);
}
