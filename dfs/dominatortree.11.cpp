// Dominator tree

#include <vector>
#include <numeric>
using namespace std;

/*snippet-begin*/
struct dominator_tree {
    vector<vector<int>> g, rg, bucket;
    vector<int> arr, par, rev, sdom, dom, dsu, label;
    int n, t;
    dominator_tree(int n) : g(n), rg(n), bucket(n), arr(n, -1),
        par(n), rev(n), sdom(n), dom(n), dsu(n), label(n), n(n), t(0) {}
    void add_edge(int u, int v) { g[u].push_back(v); }
    void dfs(int u) {
        arr[u] = t;
        rev[t] = u;
        label[t] = sdom[t] = dsu[t] = t;
        t++;
        for (int w : g[u]) {
            if (arr[w] == -1) {
                dfs(w);
                par[arr[w]] = arr[u];
            }
            rg[arr[w]].push_back(arr[u]);
        }
    }
    int find(int u, int x=0) {
        if (u == dsu[u])
            return x ? -1 : u;
        int v = find(dsu[u], x+1);
        if (v < 0)
            return u;
        if (sdom[label[dsu[u]]] < sdom[label[u]])
            label[u] = label[dsu[u]];
        dsu[u] = v;
        return x ? v : label[u];
    }
    vector<int> run(int root = 0) {
        dfs(root);
        iota(dom.begin(), dom.end(), 0);
        for (int i=t-1; i>=0; i--) {
            for (int w : rg[i])
                sdom[i] = min(sdom[i], sdom[find(w)]);
            if (i)
                bucket[sdom[i]].push_back(i);
            for (int w : bucket[i]) {
                int v = find(w);
                if (sdom[v] == sdom[w])
                    dom[w] = sdom[w];
                else
                    dom[w] = v;
            }
            if (i > 1)
                dsu[i] = par[i];
        }
        for (int i=1; i<t; i++) {
            if (dom[i] != sdom[i])
                dom[i] = dom[dom[i]];
        }
        vector<int> outside_dom(n);
        iota(begin(outside_dom), end(outside_dom), 0);
        for (int i=0; i<t; i++)
            outside_dom[rev[i]] = rev[dom[i]];
        return outside_dom;
    }
};
/*snippet-end*/

int main() {
    dominator_tree a(5);
    a.add_edge(0, 1);
    a.add_edge(1, 3);
    a.add_edge(0, 2);
    a.add_edge(2, 3);
    a.add_edge(3, 4);

    auto b = a.run();
    return b != vector<int>{0, 0, 0, 0, 3};
}
