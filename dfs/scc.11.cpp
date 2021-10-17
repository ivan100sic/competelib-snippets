// Strongly connected components

#include <vector>
#include <string>
using namespace std;

/*snippet-begin*/
struct scc {
    vector<vector<int>> e;
    vector<int> i, l, s;
    string p;
    int t;

    scc(int n) : e(n) {}

    void init() {
        i = l = vector<int>(e.size());
        p = string(e.size(), 0);
        t = 0;
    }

    void add_edge(int x, int y) {
        e[x].push_back(y);
    }

    template<class B, class A>
    void dfs(int x, B b, A a) {
        i[x] = l[x] = ++t;
        s.push_back(x);
        p[x] = 1;
        for (int y : e[x]) {
            if (!i[y]) {
                dfs(y, b, a);
                l[x] = min(l[x], l[y]);
            } else if (p[y]) {
                l[x] = min(l[x], i[y]);
            }
        }

        if (i[x] == l[x]) {
            b();
            while (1) {
                int y = s.back();
                s.pop_back();
                p[y] = 0;
                a(y);
                if (y == x) break;
            }
        }
    }

    template<class B, class A>
    void run(B b, A a) {
        for (int x=0; x<(int)e.size(); x++) {
            if (!i[x]) {
                dfs(x, b, a);
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
    scc a(4);
    a.add_edge(0, 1);
    a.add_edge(1, 0);
    a.add_edge(1, 2);
    a.add_edge(2, 3);
    a.add_edge(3, 2);

    return a.colors() != vector<int>{1, 1, 0, 0};
}
