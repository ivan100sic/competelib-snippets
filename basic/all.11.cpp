// Begin and end iterators, comma separated 

#include <vector>
#include <algorithm>
using namespace std;

#define SNIPPET_ARG(x, y) a

int main() {
    int a[5] = {5, 2, 4, 1, 3};
    sort(/*snippet-begin*/begin(SNIPPET_ARG(1, sequence)), end(SNIPPET_ARG(1, sequence))/*snippet-end*/);
    return !std::is_sorted(a, a+5);
}
