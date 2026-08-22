// Euler tour on undirected graphs

#include <vector>
#include <list>
using namespace std;

/*snippet-begin*/
struct euler_tour {
    struct edge { list<int>::iterator p, q; int u, v; };
    vector<list<int>> e;
    vector<edge> f;
    euler_tour(int n) : e(n) {}
    void add_edge(int x, int y) {
        int i = f.size();
        if (x == y) {
            e[x].push_back(i);
            auto it = --e[x].end();
            f.push_back({it, it, x, y});
        } else {
            e[x].push_back(i);
            e[y].push_back(i);
            f.push_back({--e[x].end(), --e[y].end(), x, y});
        }
    }

    list<int> dfs(int x) {
        list<int> q;
        while (e[x].size()) {
            auto& l = f[e[x].back()];
            q.push_back(x);
            x ^= l.u ^ l.v;
            e[l.u].erase(l.p);
            if (l.u != l.v)
                e[l.v].erase(l.q);
        }
        for (auto it = q.begin(); it != q.end(); ++it) q.splice(it, dfs(*it));
        return q;
    }

    vector<int> operator()(int x) {
        auto q = dfs(x);
        return vector<int>(begin(q), end(q));
    }
};
/*snippet-end*/

int main() {
    euler_tour et1(1);
    et1.add_edge(0, 0);
    if (et1(0).size() != 1) return 1;

    euler_tour et2(2);
    et2.add_edge(0, 0);
    et2.add_edge(0, 1);
    if (et2(0).size() != 2) return 1;

    euler_tour et3(3);
    et3.add_edge(0, 1);
    et3.add_edge(1, 2);
    et3.add_edge(2, 0);
    if (et3(0).size() != 3) return 1;
}
