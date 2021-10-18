// Union-find with more tracking

#include <vector>
#include <set>
#include <algorithm>
using namespace std;

/*snippet-begin*/
struct union_find_fat {
    vector<vector<int>> a;
    vector<int> b;
    set<int> r;

    union_find_fat(int n) : a(n), b(n) {
        for (int i=0; i<n; i++) {
            a[i] = {i};
            b[i] = i;
            r.emplace_hint(r.end(), i);
        }
    }

    bool join(int x, int y) {
        x = b[x];
        y = b[y];
        if (x == y) return false;
        if (a[x].size() > a[y].size()) swap(x, y);
        a[y].insert(a[y].end(), begin(a[x]), end(a[x]));
        for (int z : a[x]) b[z] = y;
        a[x].clear();
        r.erase(x);
        return true;
    }
};
/*snippet-end*/

int main() {
    union_find_fat uff(5);
    uff.join(0, 1);
    uff.join(1, 2);
    int root = uff.b[0];
    auto c = uff.a[root];
    sort(c.begin(), c.end());
    return c != vector<int>{0, 1, 2};
}
