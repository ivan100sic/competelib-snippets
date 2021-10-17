// Bridges (2-edge connected components)

#include <vector>
#include <set>
using namespace std;

/*snippet-begin*/
struct bridges {
    vector<vector<int>> e;
    vector<int> i, l, s;
    int t;

    // Multiple edges are supported
    bridges(int n) : e(n) {}

    void init() {
        i = l = vector<int>(e.size());
        t = 0;
    }

    void add_edge(int x, int y) {
        e[x].push_back(y);
        e[y].push_back(x);
    }

    template<class B, class A>
    void dfs(int x, int p, B b, A a) {
        i[x] = l[x] = ++t;
        s.push_back(x);
        bool c = 1;
        for (int y : e[x]) {
            if (c && y == p) {
                c = 0;
                continue;
            }

            if (!i[y]) {
                dfs(y, x, b, a);
                l[x] = min(l[x], l[y]);
            } else {
                l[x] = min(l[x], i[y]);
            }
        }

        if (i[x] == l[x]) {
            b();
            while (1) {
                int z = s.back();
                s.pop_back();
                a(z);
                if (z == x) break;
            }
        }
    }

    template<class B, class A>
    void run(B b, A a) {
        for (int x=0; x<(int)e.size(); x++) {
            if (!i[x]) {
                dfs(x, -1, b, a);
            }
        }
    }

    vector<vector<int>> components() {
        init();
        vector<vector<int>> z;
        run([&]() { z.emplace_back(); }, [&](int x) { z.back().push_back(x); });
        return z;
    }

    vector<int> colors() {
        init();
        vector<int> c = i;
        int k = -1;
        run([&]() { k++; }, [&](int x) { c[x] = k; });
        return c;
    }
};
/*snippet-end*/

int main() {
    bridges b(5);

    b.add_edge(0, 1);
    b.add_edge(1, 2);
    b.add_edge(2, 0);
    b.add_edge(2, 3);
    b.add_edge(3, 4);

    set<set<int>> s;
    for (auto co : b.components()) {
        s.insert(set<int>(co.begin(), co.end()));
    }

    return s != set<set<int>> { {0, 1, 2}, {3}, {4}};
}
