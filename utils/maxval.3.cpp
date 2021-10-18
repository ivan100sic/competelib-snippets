// Maximum accumulator

#include <limits>
#include <algorithm>
using namespace std;

/*snippet-begin*/
template<class T = int>
struct maxval {
    T x;
    maxval(T x = numeric_limits<T>::min()) : x(x) {}
    T operator() () const { return x; }
    maxval operator+ (const maxval& b) const { return max(x, b.x); }
    maxval& operator+= (const maxval& b) { x = max(x, b.x); return *this; }
};
/*snippet-end*/

int main() {
    maxval<int> x = 1;
    x = x + 2;
    if (x() != 2) return 1;
    (x += 3) += 4;
    if (x() != 4) return 1;
}
