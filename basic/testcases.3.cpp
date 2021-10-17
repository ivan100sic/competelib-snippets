// Testcases

#include <iostream>
#include <sstream>
using namespace std;

#define SNIPPET_ARG(x, y, z) z
#define RWI { int x; cin >> x; cout << 2*x << ' '; }

int main() {
    istringstream cin("3 1 2 3");
    ostringstream cout;
    /*snippet-begin*/
    int t;
    cin >> t;
    while (t--) {
        SNIPPET_ARG(0,,RWI)
    }
    /*snippet-end*/
    return cout.str() != "2 4 6 ";
}
