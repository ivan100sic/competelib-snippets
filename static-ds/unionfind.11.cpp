// Union-find

#include <vector>
#include <numeric>
using namespace std;

/*snippet-begin*/
struct union_find {
    vector<int> p;
    union_find(int n) : p(n) { iota(begin(p), end(p), 0); }
    bool operator() (int x, int y) { return e(x) == e(y); }
    int e(int x) {
        if (p[x] == x) return x;
        return p[x] = e(p[x]);
    }
    bool join(int x, int y) {
        x = e(x), y = e(y);
        if (x == y) return false;
        p[x] = y;
        return true;
    }
};
/*snippet-end*/

int main() {
    union_find uf(5);
    uf.join(0, 1);
    if (uf(0, 2)) return 1;
    uf.join(1, 2);
    if (!uf(0, 2)) return 1;
}
