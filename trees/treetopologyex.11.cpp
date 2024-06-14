// Tree topology (advanced, LCA, loglinear)

#include <vector>
#include <utility>
#include <tuple>
using namespace std;

// taken from treetopology.11
struct tree_topology {
    int n;
    vector<int> p, d, l, r;
    vector<vector<int>> e;

    void dfs(int x, int& t) {
        l[x] = t++;
        for (int y : e[x]) {
            if (y == p[x]) continue;
            d[y] = d[x] + 1;
            p[y] = x;
            dfs(y, t);
        }
        r[x] = t;
    }

    tree_topology(const vector<pair<int, int>>& b) {
        n = b.size() + 1;
        p.resize(n);
        e.resize(n);
        d = l = r = p;
        for (auto l : b) {
            int x, y;
            tie(x, y) = l;
            e[x].push_back(y);
            e[y].push_back(x);
        }
        p[0] = -1;
        int t = 0;
        dfs(0, t);
    }

    bool above(int x, int y) {
        return l[x] <= l[y] && r[y] <= r[x];
    }

    int size(int x) {
        return r[x] - l[x];
    }
};
// end taken

/*snippet-begin*/
struct tree_topology_ex : tree_topology {
    int logd;
    vector<vector<int>> a;

    tree_topology_ex(const vector<pair<int, int>>& b, int logd) : tree_topology(b), logd(logd) {
        a.resize(logd);
        a[0] = p;
        for (int i=1; i<logd; i++) {
            a[i].resize(n);
            for (int j=0; j<n; j++) {
                a[i][j] = a[i-1][j] == -1 ? -1 : a[i-1][a[i-1][j]];
            }
        }
    }

    int lift(int x, int k) {
        for (int i=0; i<logd; i++) {
            if (x == -1) return -1;
            if (k & (1 << i)) x = a[i][x];
        }
        return x;
    }

    int lca(int x, int y) {
        if (d[x] > d[y]) swap(x, y);
        y = lift(y, d[y] - d[x]);
        if (x == y) return x;
        for (int i=logd-1; i>=0; i--) {
            int u = a[i][x], v = a[i][y];
            if (u != v) x = u, y = v;
        }
        return p[x];
    }

    int distance(int x, int y) {
        int z = lca(x, y);
        return d[x] + d[y] - 2*d[z];
    }

    int kth(int x, int y, int k) {
        int z = lca(x, y);
        if (k <= d[x] - d[z]) {
            return lift(x, k);
        } else {
            return lift(y, d[x] + d[y] - 2*d[z] - k);
        }
    }
};
/*snippet-end*/

int main() {
    tree_topology_ex tt({{0, 1}, {1, 2}, {1, 3}}, 3);

    cout << tt.kth(2, 3, 1);

    return tt.lca(2, 3) != 1 || tt.distance(2, 3) != 2;
}
