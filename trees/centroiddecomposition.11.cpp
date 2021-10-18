// Centroid decomposition

#include <string>
#include <vector>
#include <tuple>
#include <utility>
using namespace std;

/*snippet-begin*/
struct centroid_decomposition {
    int n;
    vector<vector<int>> e;
    string b;
    vector<int> s;

    centroid_decomposition(const vector<pair<int, int>>& g) {
        int n = g.size() + 1;
        e.resize(n);
        s.resize(n);
        b = string(n, 0);
        for (auto l : g) {
            int x, y;
            tie(x, y) = l;
            e[x].push_back(y);
            e[y].push_back(x);
        }
        solve(0);
    }

    void dfs_size(int x, int p) {
        s[x] = 1;
        for (int y : e[x]) {
            if (y == p || b[y]) continue;
            dfs_size(y, x);
            s[x] += s[y];
        }
    }

    void dfs_centroid(int x, int p, int w, int& c) {
        bool ok = 1;
        for (int y : e[x]) {
            if (y == p || b[y]) continue;
            dfs_centroid(y, x, w, c);
            if (2*s[y] > w) ok = false;
        }
        if (x != p && 2*(w-s[x]) > w) ok = false;
        if (ok) c = x;
    }

    void solve(int x) {
        dfs_size(x, x);
        int c = x;
        dfs_centroid(x, x, s[x], c);
        b[c] = 1;
        // Prepare for dfs
        for (int y : e[c]) {
            if (b[y]) continue;
            // Gather subtree info
            dfs(y, c);
            // Process info
        }

        for (int y : e[c]) {
            if (!b[y]) solve(y);
        }
    }

    void dfs(int x, int p) {
        // Enter node
        for (int y : e[x]) {
            if (b[y] || y == p) continue;
            // Process and recurse
            dfs(y, x); 
        }
    }
};
/*snippet-end*/

int main() {
    centroid_decomposition tt({{0, 1}, {1, 2}, {1, 3}});
}
