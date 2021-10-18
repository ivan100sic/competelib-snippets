// Variables with built-in I/O

#include <iostream>
#include <vector>
#include <string>
using namespace std;

using ll = long long;

/*snippet-begin*/
template<class T>
struct in {
    T x;
    in () : x() { cin >> x; }
    in (const T& x) : x(x) {}
    in (T&& x) : x(x) {}
    operator T& () { return x; }
    operator const T& () const { return x; }
};

template<class T>
struct out {
    T x;
    out () : x() {}
    out (const T& x) : x(x) {}
    out (T&& x) : x(x) {}
    operator T& () { return x; }
    operator const T& () const { return x; }
    ~out() { cout << x << ' '; }
};

typedef in<int> iint;
typedef out<int> oint;
typedef in<ll> ill;
typedef out<ll> oll;
typedef in<string> istr;
typedef out<string> ostr;
typedef vector<int> vi;
typedef vector<iint> ivi;
typedef vector<oint> ovi;
/*snippet-end*/

int main() {
    return 0;
}
