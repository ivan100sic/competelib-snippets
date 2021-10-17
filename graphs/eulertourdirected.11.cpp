// Euler tour on directed graphs

#include <vector>
#include <list>
using namespace std;

/*snippet-begin*/
struct euler_tour_directed {
    vector<vector<int>> e;
    euler_tour_directed(int n) : e(n) {}
    void add_edge(int x, int y) {
        e[x].push_back(y);
    }

    list<int> dfs(int x) {
        list<int> q;
        while (e[x].size()) {
            q.push_back(x);
            int y = e[x].back();
            e[x].pop_back();
            x = y;
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
    euler_tour_directed et(3);
    et.add_edge(0, 1);
    et.add_edge(1, 2);
    et.add_edge(2, 0);

    return et(0).size() != 3;
}
