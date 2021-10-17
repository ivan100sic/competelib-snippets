// Minimum cost maximum flow (SPFA)

#include <vector>
#include <limits>
#include <string>
using namespace std;

/*snippet-begin*/
template<class T = int>
struct min_cost_max_flow {
    constexpr static T inf() { return numeric_limits<T>::max(); };

    struct edge {
        int v, t;
        T c, w, f;
    };

    vector<vector<edge>> g;
    int n, s, t;
    T f, w;

    min_cost_max_flow(int n, int s, int t) : g(n), n(n), s(s), t(t), f(T()), w(T()) {}

    void add_edge(int u, int v, T c, T w, T f = T()) {
        edge e1 = {v, (int)g[v].size(), c, w, f};
        edge e2 = {u, (int)g[u].size(), 0, -w, -f};
        g[u].push_back(e1);
        g[v].push_back(e2);
    }

    void step(T h = inf()) {
        string l(n, 0);
        vector<T> d(n, inf());
        vector<int> p(n), q(n), pe(n);
        int qs = 0, qe = 0;
        q[qe++] = s;
        d[s] = T();
        while (qs != qe) {
            int u = q[qs++];
            if (qs == n) qs = 0;
            l[u] = 2;
            for (size_t i=0; i<g[u].size(); i++) {
                edge& e = g[u][i];
                int v = e.v;
                if (e.f < e.c && d[u] + e.w < d[v]) {
                    d[v] = d[u] + e.w;
                    if (l[v] == 0) {
                        q[qe++] = v;
                        if (qe == n) qe = 0;
                    } else if (l[v] == 2) {
                        if (--qs == -1) {
                            qs = n-1;
                        }
                        q[qs] = v;
                    }
                    l[v] = 1;
                    p[v] = u;
                    pe[v] = i;
                }
            }
        }
        if (d[t] == inf()) return;
        T a = h;
        int y = t;
        while (y != s) {
            int x = p[y];
            int i = pe[y];
            a = min(a, g[x][i].c - g[x][i].f);
            y = x;
        }
        y = t;
        while (y != s) {
            int x = p[y];
            int i = pe[y];
            int j = g[x][i].t;
            g[x][i].f += a;
            g[y][j].f -= a;
            w += g[x][i].w * a;
            y = x;
        }
        f += a;
    }

    void operator()(T l = inf()) {
        while (1) {
            T o = f;
            step(l - f);
            if (o == f) return;
        }
    }
};
/*snippet-end*/

int main() {
    min_cost_max_flow<int> f(3, 0, 2);
    f.add_edge(0, 2, 10, 4);
    f.add_edge(0, 1, 3, 10);
    f.add_edge(1, 2, 2, 15);

    f();
    if (f.f != 12) return 1;
    if (f.w != 90) return 1;
}
