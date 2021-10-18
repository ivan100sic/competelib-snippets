// Min-Plus semiring (unsafe)

#include <limits>
#include <algorithm>
using namespace std;

/*snippet-begin*/
template<class T>
struct minplus {
    T x;
    minplus(T x = numeric_limits<T>::max() / 2) : x(x) {}
    T operator() () const { return x; }
    minplus operator+ (const minplus& b) const { return min(x, b.x); }
    // Unsafe chained multiplication. Use with caution.
    minplus operator* (const minplus& b) const { return x + b.x; }
    minplus& operator+= (const minplus& b) { return *this = *this + b; }
    minplus& operator*= (const minplus& b) { return *this = *this * b; }
};
/*snippet-end*/

int main() {
    minplus<int> a(3), b(4);

    if ((a+b)() != 3) return 1;
    if ((a*b)() != 7) return 1;
}
