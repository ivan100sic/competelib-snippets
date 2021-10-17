// Mexer (Generic)

#include <vector>
#include <algorithm>
using namespace std;

/*snippet-begin*/
struct mexer {
    vector<int> a;
    void operator+= (int x) { a.push_back(x); }
    int operator() () const {
        int n = a.size();
        vector<char> u(n);
        for (int x : a) if (x < n) u[x] = 1;
        return find(begin(u), end(u), 0) - begin(u);
    }
};
/*snippet-end*/

int main() {
    mexer mx;
    mx += 0;
    mx += 1;
    mx += 2;
    mx += 4;

    return mx() != 3;
}
