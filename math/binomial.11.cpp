// Binomials

#include <vector>
using namespace std;
using mint = int;

/*snippet-begin*/
template<class T = mint>
struct binomial {
    vector<T> f, finv;

    binomial(int n) : f(n), finv(n) {
        f[0] = finv[0] = 1;
        for (int i=1; i<n; i++) {
            f[i] = f[i-1] * i;
            finv[i] = T(1) / f[i];
        }
    }

    T mix(int a, int b) {
        if (a < 0 || b < 0)
            return 0;
        return f[a+b] * finv[a] * finv[b];
    }

    T choose(int n, int k) {
        return mix(n-k, k);
    }
};
/*snippet-end*/

int main() {
    binomial<double> bk(5);
    return bk.choose(4, 2) != 6;
}
