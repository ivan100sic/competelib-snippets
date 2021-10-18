// Tree topology (basic, linear time)

#include <vector>
#include <utility>
#include <tuple>
using namespace std;

/*snippet-begin*/
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
/*snippet-end*/

int main() {
    tree_topology tt({{0, 1}, {1, 2}, {1, 3}});

    return tt.size(0) != 4 || tt.size(1) != 3;
}
