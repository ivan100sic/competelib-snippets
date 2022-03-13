// Dijkstra's single source shortest path algorithm

#include <vector>
#include <set>
#include <cmath>
#include <limits>
using namespace std;

/*snippet-begin*/
template<class T = int>
struct dijkstra {
    int n, s;
    vector<vector<pair<int, T>>> e;
    vector<T> d;

    dijkstra(int n, int s=0) : n(n), s(s), e(n) {}

    void add_edge(int u, int v, T w) {
        e[u].emplace_back(v, w);
    }

    void run() {
        d.resize(n, numeric_limits<T>::max());
        set<pair<T, int>> q;
        q.emplace(T{0}, s);
        d[s] = T{0};
        while (q.size()) {
            auto it = q.begin();
            auto dx = it->first;
            auto x = it->second;
            q.erase(it);
            for (auto& g : e[x]) {
                int y = g.first;
                T w = g.second;
                if (dx + w < d[y]) {
                    q.erase({d[y], y});
                    d[y] = dx + w;
                    q.insert({d[y], y});
                }
            } 
        }
    }

    T operator[](int x) {
        if (d.empty()) run();
        return d[x];
    }
};
/*snippet-end*/

int main() {
    dijkstra<double> d(1000);
    d.add_edge(0, 123, 3.14159);
    d.add_edge(123, 999, 2.71);
    d.add_edge(0, 666, 1);
    d.add_edge(666, 999, 10);

    return fabs(d[999] - (3.14159 + 2.71)) < 1e-9 ? 0 : 1;
}
