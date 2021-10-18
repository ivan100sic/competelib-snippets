// Bit lattice

#include <vector>
using namespace std;

/*snippet-begin*/
template<class T>
struct bit_lattice {
    int N, n;
    vector<T> a;

    bit_lattice(const vector<T>& a) : N(a.size()), n(__builtin_ctz(N)), a(a) {}
    bit_lattice(int n) : N(1 << n), n(n), a(N) {}
    T& operator[] (int x) { return a[x]; }
    const T& operator[] (int x) const { return a[x]; }

    template<int Up, class F, class G>
    static void loop(int N, F f, G g) {
        for (int i=1; i<N; i<<=1)
            for (int j=(Up?0:N-1); j!=(Up?N:-1); j+=(Up?1:-1))
                if (j & i) f(g(j - i), g(j));
    }

    template<int Up, class F>
    void loop(F f) {
        loop<Up>(N, f, [this](int x) -> T& { return a[x]; });
    }

    void mul(const bit_lattice& b) { for (int i=0; i<N; i++) a[i] *= b[i]; }
    void mul(T b) { for (int i=0; i<N; i++) a[i] *= b; }

    void sos() { loop<1>([](T& l, T& h) { h += l; }); }
    void sos_inv() { loop<0>([](T& l, T& h) { h -= l; }); }
    void sos_zero() { loop<1>([](T& l, T& h) { l += h; }); }
    void sos_zero_inv() { loop<0>([](T& l, T& h) { l -= h; }); }
    void fft2n() { loop<1>([](T& l, T& h) { T s = l + h, d = l - h; l = s; h = d; }); }

    void operator|= (bit_lattice b) { sos(); b.sos(); mul(b); sos_inv(); }
    void operator&= (bit_lattice b) { sos_zero(); b.sos_zero(); mul(b); sos_zero_inv(); }
    void operator^= (bit_lattice b) { fft2n(); b.fft2n(); mul(b); fft2n(); mul(T(1) / T(N)); }

    // Subset convolution
    void add_sc(T* a, T* b) const {
        for (int i=0; i<=n; i++) a[i] += b[i]; 
    }

    void sub_sc(T* a, T* b) const {
        for (int i=0; i<=n; i++) a[i] -= b[i]; 
    }

    void mul_sc(T* a, T* b) const {
        for (int i=n; i>=0; i--) {
            T t = 0;
            for (int j=0; j<=i; j++) t += a[j] * b[i-j];
            a[i] = t;
        }
    }

    vector<T> sos_sc() const {
        vector<T> b(N*(n+1));
        for (int i=0; i<N; i++) b[i*(n+1)+__builtin_popcount(i)] = a[i];
        loop<1>(N, [this](T* a, T* b) { add_sc(b, a); }, [&, this](int i) { return b.data()+i*(n+1); });
        return b;
    }

    void sos_inv_sc(vector<T>& b) const {
        loop<0>(N, [this](T* a, T* b) { sub_sc(b, a); }, [&, this](int i) { return b.data()+i*(n+1); });
    }

    [[nodiscard]] bit_lattice subset_conv(const bit_lattice& b) const {
        auto c = sos_sc();
        auto d = b.sos_sc();
        for (int i=0; i<N*(n+1); i+=n+1) mul_sc(c.data()+i, d.data()+i);
        sos_inv_sc(c);
        bit_lattice e(n);
        for (int i=0; i<N; i++) e[i] = c[i*(n+1) + __builtin_popcount(i)];
        return e;
    }
};
/*snippet-end*/

int main() {
    bit_lattice<int> a(2);
    a[1] = 1;
    a.sos();
    int b[4] = {0, 1, 0, 1};
    return !equal(&a[0], &a[4], b);
}
