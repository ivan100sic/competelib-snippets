// Basic program skeleton

#define SNIPPET_ARG(x, y, a) a
#define BODY int sum = 0; for (int x : ra(0, 5)) sum += x; return sum != 10;

/*snippet-begin*/
// Retired?
#include <bits/stdc++.h>
using namespace std;

namespace R = ranges;
auto ra(auto x, auto y) { return R::iota_view(x, y); }

using ll = long long;
using ull = long unsigned long;
using ld = double long;

int main() {
    ios::sync_with_stdio(!cin.tie(0));

    SNIPPET_ARG(0,,BODY)
}
/*snippet-end*/
