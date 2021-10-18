// Union-find with rollback

#include <vector>
#include <utility>
#include <tuple>
using namespace std;

/*snippet-begin*/
struct union_find_rollback {
    struct elem { int p, s; };
    vector<elem> a;
    vector<pair<int*, int>> u;

    int root(int x) {
        while (x != a[x].p) x = a[x].p;
        return x;
    }

    void flag() { u.emplace_back(nullptr, 0); }
    void mark(int& x) { u.emplace_back(&x, x); }
    bool operator() (int x, int y) { return root(x) == root(y); }

    union_find_rollback(int n) : a(n) {
        for (int i=0; i<n; i++) a[i] = {i, 1};
    }

    void join(int x, int y) {
        x = root(x); y = root(y);
        if (x == y) return;
        if (a[x].s > a[y].s) {
            swap(x, y);
        }
        mark(a[x].p); mark(a[y].s);
        a[x].p = y;
        a[y].s += a[x].s;
    }

    void rollback() {
        while (1) {
            int* p, v;
            tie(p, v) = u.back(); u.pop_back();
            if (p) {
                *p = v;
            } else {
                return;
            }
        }
    }
};
/*snippet-end*/

int main() {
    union_find_rollback ufr(5);
    if (ufr(0, 1)) return 1;
    ufr.flag();
    ufr.join(0, 1);
    if (!ufr(0, 1)) return 1;
    ufr.rollback();
    if (ufr(0, 1)) return 1;
}
