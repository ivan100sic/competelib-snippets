// Fractional cascading

#include <vector>
#include <algorithm>
using namespace std;

/*snippet-begin*/
template<class T = int>
struct fractional_cascading {
    int maxn;
    vector<vector<T>> a;
    vector<vector<int>> pl, pr;

    fractional_cascading(const vector<vector<T>>& b) {
        int n = b.size();
        maxn = 1;
        while (maxn < n)
            maxn <<= 1;
        a.resize(2*maxn);
        copy(b.begin(), b.end(), a.begin() + maxn);
        build();
    }

    fractional_cascading(const vector<pair<int, T>>& b) {
        int n = 1;
        maxn = 1;
        for (const auto& kv : b)
            n = max(n, kv.first+1);
        while (maxn < n)
            maxn <<= 1;
        a.resize(2*maxn);
        for (const auto& kv : b)
            a[kv.first + maxn].push_back(kv.second);
        build();
    }

    void build() {
        pl.resize(maxn);
        pr.resize(maxn);
        for (int i=0; i<maxn; i++)
            sort(begin(a[i+maxn]), end(a[i+maxn]));
        for (int i=maxn-1; i; i--) {
            size_t sl = 0, sr = 0, si = 0, q = a[2*i].size() + a[2*i+1].size();
            pl[i].resize(q+1);
            pr[i].resize(q+1);
            a[i].resize(q);
            while (si < q) {
                int r;
                if (sr == a[2*i+1].size()) r = 0;
                else if (sl == a[2*i].size()) r = 1;
                else r = a[2*i+1][sr] < a[2*i][sl];
                a[i][si++] = a[2*i+r][(r ? sr : sl)++];
                pl[i][si] = sl;
                pr[i][si] = sr;
            }
        }
    }

    template<class F>
    void get(int l, int r, F f, int x, int xl, int xr, int yl, int yr) const {
        if (r <= xl || xr <= l || yl == yr)
            return;
        if (l <= xl && xr <= r)
            return f(x, yl, yr);
        int xm = (xl+xr) >> 1;
        get(l, r, f, 2*x, xl, xm, pl[x][yl], pl[x][yr]);
        get(l, r, f, 2*x+1, xm, xr, pr[x][yl], pr[x][yr]);
    }

    template<class F>
    void operator() (int l, int r, const T& lo, const T& hi, F f) const {
        int yl = lower_bound(begin(a[1]), end(a[1]), lo) - begin(a[1]);
        int yr = lower_bound(begin(a[1]), end(a[1]), hi) - begin(a[1]);
        get(l, r, f, 1, 0, maxn, yl, yr);
    }
};
/*snippet-end*/

int main() {
    fractional_cascading<int> fc({{1}, {1, 2}, {1, 2, 3}});

    int c = 0;
    fc(0, 3, 0, 3, [&c](int x, int y, int z) { c++; });

    return c != 2;
}
