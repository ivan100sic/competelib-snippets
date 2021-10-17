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
        e[x].push_back(i);
        e[y].push_back(i);
        f.push_back({--e[x].end(), --e[y].end(), x, y});
    }

    list<int> dfs(int x) {
        list<int> q;
        while (e[x].size()) {
            auto& l = f[e[x].back()];
            q.push_back(x);
            x ^= l.u ^ l.v;
            e[l.u].erase(l.p);
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
    euler_tour et(3);
    et.add_edge(0, 1);
    et.add_edge(1, 2);
    et.add_edge(2, 0);

    return et(0).size() != 3;
}
