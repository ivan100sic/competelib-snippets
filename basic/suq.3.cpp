// Sort and unique-ify

#include <vector>
#include <algorithm>
using namespace std;

#define SNIPPET_ARG(x) a

const int ad[7] = {5, 4, 1, 3, 4, 2, 5};
const int bd[5] = {1, 2, 3, 4, 5};

int main() {
    vector<int> a(ad, ad+7);
    vector<int> b(bd, bd+5);
    
    /*snippet-begin*/
    sort(SNIPPET_ARG(1).begin(), SNIPPET_ARG(1).end());
    SNIPPET_ARG(1).erase(unique(SNIPPET_ARG(1).begin(), SNIPPET_ARG(1).end()), SNIPPET_ARG(1).end());
    /*snippet-end*/
    
    return !(a == b);
}
