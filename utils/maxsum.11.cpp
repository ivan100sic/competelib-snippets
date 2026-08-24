// Max subarray sum

#include <algorithm>
using namespace std;

/*snippet-begin*/
template<class T>
struct max_sum {
    T s, l, r, a;

    max_sum(T x) { s = l = r = a = x; }

    max_sum operator+ (const max_sum& b) const {
        max_sum z;
        z.s = s + b.s;
        z.l = max(l, s + b.l);
        z.r = max(r + b.s, b.r);
        z.a = max({a, b.a, r + b.l});
        return z;
    }

    max_sum& operator+= (const max_sum& b) {
        return *this = *this + b;
    }

private:
    max_sum() {}
};
/*snippet-end*/

int main() {
    max_sum<int> a(-5), b(-3), c(-2);
    auto all_neg = a + b + c;
    if (all_neg.a != -2) return 1;
    if (all_neg.l != -5) return 1;
    if (all_neg.r != -2) return 1;
    if (all_neg.s != -10) return 1;

    max_sum<int> d(3), e(-1), f(9);
    auto mixed = d + e + f;
    if (mixed.a != 11) return 1;
    if (mixed.l != 11) return 1;
    if (mixed.r != 11) return 1;
    if (mixed.s != 11) return 1;

    max_sum<int> g(7);
    if ((g).a != 7) return 1;

    max_sum<int> h(5), i(5), j(5);
    if ((h + i + j).a != 15) return 1;

    auto left = (a + b) + c;
    auto right = a + (b + c);
    if (left.a != right.a || left.s != right.s || left.l != right.l || left.r != right.r)
        return 1;

    return 0;
}
