// Heavy-light decomposition

#include <algorithm>
#include <tuple>
#include <utility>
#include <vector>
using namespace std;

/*snippet-begin*/
struct hld {
    vector<int> p, h, d, r, s;

    int dfs(const vector<vector<int>>& e, int x) {
        int sz = 1, best = 0;
        for (int y : e[x]) {
            if (y == p[x])
                continue;
            p[y] = x;
            d[y] = d[x] + 1;
            int z = dfs(e, y);
            if (z > best) {
                best = z;
                h[x] = y;
            }
            sz += z;
        }
        return sz;
    }

    hld(const vector<pair<int, int>>& e, int root = 0) {
        int n = e.size() + 1;
        p = h = d = r = s = vector<int>(n, -1);
        d[root] = 0;

        vector<vector<int>> g(n);
        for (auto l : e) {
            int x, y;
            tie(x, y) = l;
            g[x].push_back(y);
            g[y].push_back(x);
        }

        dfs(g, root);

        int k = 0;
        for (int i=0; i<n; i++) {
            if (i == root || h[p[i]] != i) {
                for (int j=i; j!=-1; j=h[j]) {
                    r[j] = i;
                    s[j] = k++;
                }
            }
        }
    }

    int operator() (int x) {
        return s[x];
    }

    template<class Up, class Dn>
    int operator() (int x, int y, Up up, Dn dn) {
        while (r[x] != r[y]) {
            if (d[r[x]] > d[r[y]]) {
                up(s[r[x]], s[x] + 1);
                x = p[r[x]];
            } else {
                dn(s[r[y]], s[y] + 1);
                y = p[r[y]];
            }
        }

        if (d[x] > d[y]) {
            up(s[y] + 1, s[x] + 1);
            return y;
        } else if (d[x] < d[y]) {
            dn(s[x] + 1, s[y] + 1);
            return x;
        } else {
            return x;
        }
    }

    template<class Op>
    int operator() (int x, int y, Op op) {
        return (*this)(x, y, op, op);
    }
};
/*snippet-end*/

int main() {
    hld t({{0, 1}, {1, 2}, {1, 3}, {2, 4}, {4, 5}}, 0);
    int n = t.s.size();

    for (int i=0; i<n; i++)
        if (t(i) < 0 || t(i) >= n) return 1;

    for (int i=0; i<n; i++)
        for (int j=i+1; j<n; j++)
            if (t(i) == t(j)) return 1;

    vector<int> path;
    auto add = [&](int l, int r) {
        for (int i=l; i<r; i++)
            path.push_back(i);
    };

    if (t(5, 3, add, add) != 1) return 1;

    sort(path.begin(), path.end());
    if (path != vector<int>{2, 3, 4, 5}) return 1;

    int calls = 0;
    auto inc = [&](int, int) { calls++; };
    if (t(3, 3, inc, inc) != 3) return 1;
    if (calls != 0) return 1;

    return 0;
}
