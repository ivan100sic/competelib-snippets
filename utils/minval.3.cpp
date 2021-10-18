// Minimum accumulator

#include <limits>
#include <algorithm>
using namespace std;

/*snippet-begin*/
template<class T = int>
struct minval {
    T x;
    minval(T x = numeric_limits<T>::max()) : x(x) {}
    T operator() () const { return x; }
    minval operator+ (const minval& b) const { return min(x, b.x); }
    minval& operator+= (const minval& b) { x = min(x, b.x); return *this; }
};
/*snippet-end*/

int main() {
    minval<int> x = 4;
    x = x + 3;
    if (x() != 3) return 1;
    (x += 2) += 1;
    if (x() != 1) return 1;
}
