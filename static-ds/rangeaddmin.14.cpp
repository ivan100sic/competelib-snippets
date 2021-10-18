// Range Add Min

#include <limits>
#include <functional>
#include <algorithm>
using namespace std;

template<class A, class B, class C>
int segtreelazy(int n, A a, B b, C c, int, int, int) {
    return n;
}

/*snippet-begin*/
template<class T = int>
decltype(auto) range_add_min(int n) {
    return segtreelazy(n, [](T x, T y) { return min(x, y); }, plus<T>(), plus<T>(),
        numeric_limits<T>::max(), T(), T());
}
/*snippet-end*/

int main() {
    return range_add_min<int>(5) != 5;
}
