// Midpoint of two integers

#include <type_traits>
using std::make_unsigned;

/*snippet-begin*/
template<class T>
T midpoint(T x, T y) {
    using U = typename make_unsigned<T>::type;
    return T(U(x) + (U(y) - U(x)) / 2);
}
/*snippet-end*/

int main() {
    const int big = 2000000000;
    
    if (midpoint(0, 4) != 2) return 1;
    if (midpoint(big+1, big+3) != big+2) return 1;
    if (midpoint(-big-3, -big-1) != -big-2) return 1;
}
