// Xor basis

using ll = long long;

/*snippet-begin*/
template<int B = 60>
struct xorbasis {
    ll b[B];
    int sz;

    xorbasis() : sz(0) {
        for (int i=0; i<B; i++)
            b[i] = 0;
    }

    bool add(ll x) {
        for (int i=B-1; i>=0; i--) {
            if (!(x >> i & 1)) continue;
            if (!b[i]) {
                b[i] = x;
                sz++;
                return true;
            }
            x ^= b[i];
        }
        return false;
    }

    ll max_xor(ll x = 0) const {
        for (int i=B-1; i>=0; i--)
            if (b[i] && !(x >> i & 1))
                x ^= b[i];
        return x;
    }

    ll min_xor(ll x = 0) const {
        for (int i=B-1; i>=0; i--)
            if (b[i] && (x >> i & 1))
                x ^= b[i];
        return x;
    }

    bool contains(ll x) const {
        return min_xor(x) == 0;
    }

    ll kth(ll k) const {
        if (k < 1 || k > (1LL << sz)) return -1;
        ll x = 0;
        ll cnt = 1LL << sz;
        for (int i=B-1; i>=0; i--) {
            if (!b[i]) continue;
            if (k > cnt / 2) {
                if (!(x >> i & 1)) x ^= b[i];
                k -= cnt / 2;
            } else {
                if (x >> i & 1) x ^= b[i];
            }
            cnt /= 2;
        }
        return x;
    }

    ll count_lt(ll x) const {
        if (x < 0) return 0;
        if (x >> B) return 1LL << sz;
        ll ret = 0, cnt = 1LL << sz;
        ll mask = 0;
        for (int i=B-1; i>=0; i--) {
            if (b[i]) {
                if (x >> i & 1) {
                    ret += cnt / 2;
                    if (!(mask >> i & 1)) mask ^= b[i];
                } else {
                    if (mask >> i & 1) mask ^= b[i];
                }
                cnt /= 2;
            } else {
                if ((x ^ mask) >> i & 1) {
                    if (x >> i & 1) return ret + cnt;
                    else return ret;
                }
            }
        }
        return ret;
    }

    ll count_le(ll x) const {
        return count_lt(x) + (min_xor(x) == 0);
    }
};
/*snippet-end*/

int main() {
    xorbasis<> b;
    b.add(1);
    b.add(2);
    b.add(3);
    if (b.sz != 2) return 1;
    if (b.max_xor() != 3) return 1;
    if (b.kth(1) != 0) return 1;
    if (b.kth(2) != 1) return 1;
    if (b.kth(3) != 2) return 1;
    if (b.kth(4) != 3) return 1;
    if (b.kth(5) != -1) return 1;
    if (b.count_lt(2) != 2) return 1;
    if (b.count_le(2) != 3) return 1;
    if (!b.contains(3)) return 1;
    if (b.contains(4)) return 1;

    xorbasis<> e;
    if (e.kth(1) != 0) return 1;
    if (e.count_le(0) != 1) return 1;
}
