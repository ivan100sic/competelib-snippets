// Articulation vertices (2-vertex CCs)

#include <vector>
#include <utility>
#include <tuple>
using namespace std;

/*snippet-begin*/
struct articulation_vertices {
    vector<vector<int>> e;
    vector<pair<int, int>> b;
    vector<int> i, l, s, c;
    int k, t;

    // Multiple edges are supported
    articulation_vertices(int n, const vector<pair<int, int>>& g) :
        e(n), i(n), l(n), c(g.size()), k(0), t(0)
    {
        b = g;
        for (int i=0; i<(int)b.size(); i++) {
            int x, y;
            tie(x, y) = b[i];
            e[x].push_back(i);
            e[y].push_back(i);
        }

        for (int x=0; x<(int)e.size(); x++) {
            if (!i[x]) {
                dfs(x, -1);
            }
        }
    }

    void dfs(int x, int p) {
        i[x] = l[x] = ++t;
        int q = 1;
        for (int m : e[x]) {
            int y = b[m].first ^ b[m].second ^ x;
            if (q && y == p) {
                q = 0;
                continue;
            }
            if (i[y]) {
                if (i[y] < i[x]) {
                    l[x] = min(l[x], i[y]);
                    s.push_back(m);
                }
            } else {
                s.push_back(m);
                dfs(y, x);
                l[x] = min(l[x], l[y]);
                if (l[y] >= i[x]) {
                    while (1) {
                        int j = s.back();
                        s.pop_back();
                        c[j] = k;
                        if (j == m) {
                            break;
                        }
                    }
                    k++;
                }
            }
        }
    }

    const vector<int>& colors() const { return c; }

    vector<int> vertices() {
        vector<int> r;
        for (int x=0; x<(int)e.size(); x++) {
            int z = -1;
            for (int i : e[x]) {
                z = z == -1 ? c[i] : (z == c[i] ? z : -2);
            }
            if (z == -2) {
                r.push_back(x);
            }
        }
        return r;
    }
};
/*snippet-end*/

int main() {
    articulation_vertices av(5, {{0, 1}, {1, 2}, {2, 0}, {2, 3}, {3, 4}, {4, 2}});
    return av.vertices() != vector<int>{2};
}
