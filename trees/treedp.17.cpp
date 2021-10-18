// Tree DP

#include <vector>
#include <utility>
#include <functional>
#include <tuple>
using namespace std;

/*snippet-begin*/
template<class T, class D, class E, class G, class U, class F = plus<D>>
struct tree_dp {
    vector<T> a;
    D e;
    vector<D> up, dn, rt;
    F f;
    G g;
    U u;
    vector<pair<int, E>*> p;
    vector<vector<pair<int, E>>> h;

    // a : vertex array - typed T
    // b : array of edges - typed E
    // g : (D, T) -> D - extends the sum of subtrees with the root vertex
    // u : (D, E) -> D - extends a subtree with an edge
    // e : neutral element of D
    // f : (D, D) -> D - adds together two (extended) subtrees
    tree_dp(const vector<T>& a, const vector<tuple<int, int, E>>& b, G g, U u, D e = D(), F f = F()) :
        a(a), e(e), up(a.size()), dn(a.size()), f(f), g(g), u(u), p(a.size()), h(a.size())
    {
        for (auto [x, y, z] : b) {
            h[x].emplace_back(y, z);
            h[y].emplace_back(x, z);
        }
        dfs1(0, 0);
        dfs2(0);
        rt.resize(a.size());
        rt[0] = dn[0];
        for (int x=1; x<(int)a.size(); x++) {
            D d = u(up[x], p[x]->second);
            for (auto& hh : h[x]) {
                auto& [y, w] = hh;
                if (y != p[x]->first)
                    d = f(d, u(dn[y], w));
            }
            rt[x] = g(d, a[x]);
        }
    }

    D operator() (int x) { return rt[x]; }

    void dfs1(int x, int o) {
        D d = e;
        for (auto& hh : h[x]) {
            auto& [y, w] = hh;
            if (y == o) {
                p[x] = &hh;
                continue;
            }
            dfs1(y, x);
            d = f(d, u(dn[y], w));
        }
        dn[x] = g(d, a[x]);
    }

    void dfs2(int x) {
        D d = x ? u(up[x], p[x]->second) : e, t = e;
        int m = h[x].size() - !!x;
        vector<D> pref(m, e);
        int i = 0;
        for (auto& hh : h[x]) {
            auto& [y, w] = hh;
            if (p[x] && p[x]->first == y) continue;
            pref[i++] = t;
            t = f(t, u(dn[y], w));
        }
        for (int j=(int)h[x].size()-1; j>=0; j--) {
            auto& hh = h[x][j];
            auto& [y, w] = hh;
            if (p[x] && p[x]->first == y) continue;
            i--;
            up[y] = g(f(pref[i], d), a[x]);
            d = f(d, u(dn[y], w));
        }
        for (auto& hh : h[x]) {
            auto& [y, w] = hh;
            if (p[x] && p[x]->first == y) continue;
            dfs2(y);
        }
    }
};
/*snippet-end*/

int main() {
    vector<int> a = {1, 2, 3};
    vector<tuple<int, int, int>> b = {{0, 1, 10}, {1, 2, 20}};
    plus<int> p;

    tree_dp t(a, b, p, p, 0, p);

    return t(0) != 36 || t(1) != 36 || t(2) != 36;
}
