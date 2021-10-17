// Divisor loop

#include <tuple>
using namespace std;

/*snippet-begin*/
template<class T>
struct divisor_loop {
    T n;

    divisor_loop(T n) : n(n) {}

    struct iterator {
        T n, q, l, r;

        tuple<T, T, T> operator*() {
            return {q, l, r};
        }

        iterator& operator++() {
            if (q == 1) {
                l = r = q = 0;
            } else {
                l = r + 1;
                q = n / l;
                r = n / q;
            }
            return *this;
        }

        bool operator== (const iterator& b) const {
            return tie(n, q, l, r) == tie(b.n, b.q, b.l, b.r);
        }

        bool operator!= (const iterator& b) const {
            return !(*this == b);
        }
    };

    iterator begin() {
        return {n, n, T(1), T(1)};
    }

    iterator end() {
        return {n, T(0), T(0), T(0)};
    }
};
/*snippet-end*/

int main() {
    int z = 0;
    for (auto abc : divisor_loop<int>(10)) {
        z += get<0>(abc);
    }

    return z != 1 + 2 + 3 + 5 + 10;
}
