// Cartesian tree

#include <vector>
#include <functional>
using namespace std;

/*snippet-begin*/
struct cartesian_tree {
    vector<int> l, r, p;
    int q;

    template<class A, class C = less<typename remove_reference<decltype((*(A*)0)[0])>::type>>
    cartesian_tree(const A& a, C c = C()) {
        int n = a.size();
        l = r = p = vector<int>(n, -1);
        q = 0;
        for (int i=1; i<n; i++) {
            int j = i-1;
            while (j != -1 && c(a[i], a[j])) j = p[j];
            if (j == -1) l[i] = q, p[q] = i, q = i;
            else if (j == i-1) r[j] = i, p[i] = j;
            else l[i] = r[j], p[r[j]] = i, p[i] = j, r[j] = i;
        }
    }
};
/*snippet-end*/

int main() {
    cartesian_tree ct(vector<int>{10, 10, 7, 9, 8, 3, 3, 10, 7, 3});

    if (ct.l != vector<int>{-1, -1, 0, -1, 3, 2, -1, -1, 7, 8}) return 1;
    if (ct.r != vector<int>{1, -1, 4, -1, -1, 6, 9, -1, -1, -1}) return 1;
    if (ct.p != vector<int>{2, 0, 5, 4, 2, -1, 5, 8, 9, 6}) return 1;
    if (ct.q != 5) return 1;
}
