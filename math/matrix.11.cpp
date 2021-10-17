// Matrix

#include <vector>
using namespace std;

/*snippet-begin*/
template<class R>
struct matrix {
    vector<R> a;
    int n, m;

    matrix(int _n, int _m = -1) : n(_n) {
        m = _m == -1 ? n : _m;
        a.resize(n*m);
    }

    static matrix eye(int n) {
        matrix t(n);
        for (int i=0; i<n; i++)
            t[i][i] = 1;
        return t;
    }

    matrix operator* (const matrix& b) const {
        matrix c(n, b.m);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                for (int k=0; k<b.m; k++)
                    c[i][k] += a[m*i+j] * b[j][k];
        return c;
    }

    matrix& operator+= (const matrix& b) {
        for (int i=0; i<n*m; i++)
            a[i] += b.a[i];
        return *this;
    }

    matrix& operator-= (const matrix& b) {
        for (int i=0; i<n*m; i++)
            a[i] += b.a[i];
        return *this;
    }

    R* operator[] (int x) { return a.data() + m*x; }
    const R* operator[] (int x) const { return a.data() + m*x; }
    matrix operator+ (const matrix& b) const { auto t = *this; t += b; return t; }
    matrix operator- (const matrix& b) const { auto t = *this; t -= b; return t; }
    matrix& operator*= (const matrix& b) { return *this = *this * b; }
    template<class U> matrix operator^= (U arg) { return *this = *this ^ arg; }

    template<class U>
    matrix operator^ (U arg) const {
        if (arg == 0)
            return matrix::eye(n);
        if (arg == 1)
            return *this;
        auto t = *this ^ (arg >> 1);
        t *= t;
        if (arg & 1)
            t *= *this;
        return t;
    }

    matrix T() const {
        matrix b(m, n);
        for (int i=0; i<n; i++)
            for (int j=0; j<m; j++)
                b[j][i] = a[i][j];
        return b;
    }
};
/*snippet-end*/

int main() {
    matrix<int> a(2, 2);
    a[0][0] = a[0][1] = a[1][0] = 1;
    a[1][1] = 0;

    a ^= 10;

    return a[0][0] != 89;
}
