// Double hash

#include <chrono>
#include <vector>
#include <tuple>
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

// taken from rollinghash.17
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
// end taken

/*snippet-begin*/
template<int m1, int m2>
struct double_hash {
    rolling_hash<m1> h1;
    rolling_hash<m2> h2;

    template<class T>
    double_hash(T x) : h1(x), h2(x) {}

    double_hash() {}

    double_hash(rolling_hash<m1>&& h1, rolling_hash<m2>&& h2) : h1(h1), h2(h2) {}

    double_hash operator+ (const double_hash& b) const {
        return {h1 + b.h1, h2 + b.h2};
    }

    double_hash operator- (const double_hash& b) const {
        return {h1 - b.h1, h2 - b.h2};
    }

    bool operator< (const double_hash& b) const { return tie(h1, h2) < tie(b.h1, b.h2); };
    bool operator> (const double_hash& b) const { return tie(h1, h2) > tie(b.h1, b.h2); };
    bool operator== (const double_hash& b) const { return tie(h1, h2) == tie(b.h1, b.h2); };
    bool operator!= (const double_hash& b) const { return tie(h1, h2) != tie(b.h1, b.h2); };
    bool operator<= (const double_hash& b) const { return tie(h1, h2) <= tie(b.h1, b.h2); };
    bool operator>= (const double_hash& b) const { return tie(h1, h2) >= tie(b.h1, b.h2); };
};

using dhash = double_hash<1983933308, 1957926429>;
/*snippet-end*/

int main() {
    dhash a(1);
    dhash b(2);
    dhash c(3);

    return (a + (b + c)) != ((a + b) + c);
}
