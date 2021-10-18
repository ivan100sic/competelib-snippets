// Range Add Max

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
decltype(auto) range_add_max(int n) {
    return segtreelazy(n, [](T x, T y) { return max(x, y); }, plus<T>(), plus<T>(),
        numeric_limits<T>::min(), T(), T());
}
/*snippet-end*/

int main() {
    return range_add_max<int>(5) != 5;
}
