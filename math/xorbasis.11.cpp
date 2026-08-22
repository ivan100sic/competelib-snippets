// Xor basis

#include <cstdint>
#include <type_traits>

/*snippet-begin*/
template<int B = 60>
struct xorbasis {
    static_assert(B >= 1 && B <= 64, "B must be between 1 and 64");

    using T = typename std::conditional<B <= 8, uint8_t,
        typename std::conditional<B <= 16, uint16_t,
            typename std::conditional<B <= 32, uint32_t, uint64_t>::type>::type>::type;

    using cnt_t = typename std::conditional<B == 64, __uint128_t, uint64_t>::type;

    static constexpr T max_span() {
        return (T(1) << (B - 1)) | ((T(1) << (B - 1)) - T(1));
    }

    T b[B];
    int sz;

    xorbasis() : sz(0) {
        for (int i=0; i<B; i++)
            b[i] = T(0);
    }

    bool add(T x) {
        x &= max_span();
        for (int i=B-1; i>=0; i--) {
            if (!((x >> i) & 1)) continue;
            if (!b[i]) {
                b[i] = x;
                sz++;
                return true;
            }
            x ^= b[i];
        }
        return false;
    }

    T max_xor(T x = T(0)) const {
        for (int i=B-1; i>=0; i--)
            if (b[i] && !((x >> i) & 1))
                x ^= b[i];
        return x;
    }

    T min_xor(T x = T(0)) const {
        for (int i=B-1; i>=0; i--)
            if (b[i] && ((x >> i) & 1))
                x ^= b[i];
        return x;
    }

    bool contains(T x) const {
        return min_xor(x) == T(0);
    }

    T kth(cnt_t k) const {
        if (k < 1 || k > ((cnt_t)1 << sz)) return T(-1);
        T x = T(0);
        cnt_t cnt = (cnt_t)1 << sz;
        for (int i=B-1; i>=0; i--) {
            if (!b[i]) continue;
            if (k > cnt / 2) {
                if (!((x >> i) & 1)) x ^= b[i];
                k -= cnt / 2;
            } else {
                if ((x >> i) & 1) x ^= b[i];
            }
            cnt /= 2;
        }
        return x;
    }

    cnt_t count_lt(T x) const {
        if (x > max_span())
            return (cnt_t)1 << sz;
        cnt_t ret = 0, cnt = (cnt_t)1 << sz;
        T mask = T(0);
        for (int i=B-1; i>=0; i--) {
            if (b[i]) {
                if ((x >> i) & 1) {
                    ret += cnt / 2;
                    if (!((mask >> i) & 1)) mask ^= b[i];
                } else {
                    if ((mask >> i) & 1) mask ^= b[i];
                }
                cnt /= 2;
            } else {
                if (((x ^ mask) >> i) & 1) {
                    if ((x >> i) & 1) return ret + cnt;
                    else return ret;
                }
            }
        }
        return ret;
    }

    cnt_t count_le(T x) const {
        return count_lt(x) + (min_xor(x) == T(0));
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
    if (b.kth(5) != xorbasis<>::T(-1)) return 1;
    if (b.count_lt(2) != 2) return 1;
    if (b.count_le(2) != 3) return 1;
    if (!b.contains(3)) return 1;
    if (b.contains(4)) return 1;

    xorbasis<> e;
    if (e.kth(1) != 0) return 1;
    if (e.count_le(0) != 1) return 1;
}
