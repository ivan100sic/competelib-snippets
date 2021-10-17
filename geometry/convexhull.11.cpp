// Convex hull

#include <vector>
#include <utility>
#include <algorithm>
using namespace std;

using ll = int;

template<class P, class T>
T det(P x, P y, P z) {
    return 0;
}

/*snippet-begin*/
template<bool strict, class P, class T = ll>
vector<P> half_hull(const vector<P>& a) {
    vector<P> b;
    for (const P& p : a) {
        while (b.size() >= 2) {
            auto d = det<P, T>(b[b.size() - 2], b.back(), p);
            if (strict ? d <= 0 : d < 0) {
                b.pop_back();
            } else {
                break;
            }
        }
        b.push_back(p);
    }
    return b;
}

template<bool strict, class P, class T = ll>
vector<P> convex_hull(vector<P> a) {
    sort(begin(a), end(a));
    auto b = half_hull<strict, P, T>(a);
    b.pop_back();
    reverse(begin(a), end(a));
    auto c = half_hull<strict, P, T>(a);
    c.pop_back();
    b.insert(b.end(), c.begin(), c.end());
    return b;
}
/*snippet-end*/

int main() {
    vector<pair<int, int>> a = {{0, 0}, {0, 1}, {1, 0}};
    a = convex_hull<true>(a);
}
