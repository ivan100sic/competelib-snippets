// Chinese Remainder Theorem

// taken from snippet eea.3
template<class T>
T eea(T a, T b, T& x, T& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }

    T x1, y1;
    T g = eea(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
// end taken

using ll = long long;

/*snippet-begin*/
struct crt {
    ll i1, i2, mm, mod1, mod2;

    // mod1 * mod2 < 2^62, coprime
    crt(ll mod1, ll mod2) {
        this->mod1 = mod1;
        this->mod2 = mod2;
        eea(mod1, mod2, i1, i2);
        mm = mod1 * mod2;
        i1 = (i1 % mm + mm) % mm;
        i2 = (i2 % mm + mm) % mm;
    }

    ll operator() (ll x, ll y) const {
        x = (__int128_t)x * i2 % mm;
        y = (__int128_t)y * i1 % mm;
        ll t = (__int128_t)x * mod2 % mm + (__int128_t)y * mod1 % mm;
        return t >= mm ? t - mm : t;
    }
};
/*snippet-end*/

int main() {
    crt c(3, 5);
    return c(2, 4) != 14;
}
