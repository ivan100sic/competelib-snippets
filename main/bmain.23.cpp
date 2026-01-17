// Basic program skeleton

#define SNIPPET_ARG(x, y, a) a
#define BODY                                                        \
    return R::fold_left(                                            \
        V::zip_transform(times{}, ra(0, 5), ra(10, 20)),            \
        0, plus{}) != 130;

/*snippet-begin*/
// Retired?
#include <bits/stdc++.h>
using namespace std;

namespace R = ranges;
namespace V = R::views;
auto ra(auto x, auto y) { return V::iota(x, y); }

using ll = long long;
using ull = long unsigned long;
using ld = double long;

int main() {
    ios::sync_with_stdio(!cin.tie(0));

    SNIPPET_ARG(0,,BODY)
}
/*snippet-end*/
