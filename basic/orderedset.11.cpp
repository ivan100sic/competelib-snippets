// Ordered set

#include <utility>
using namespace std;

/*snippet-begin*/
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>
using namespace __gnu_pbds;
template<class T>
using ordered_set = tree<T, null_type, less<T>, rb_tree_tag, tree_order_statistics_node_update>;
// find_by_order(size_t) -> iterator, order_of_key(val) -> size_t
/*snippet-end*/

int main() {
    ordered_set<pair<int, int>> s;
    
    for (int i=0; i<100; i++) {
        s.insert({i, i});
    }

    return s.order_of_key({50, 1000}) != 51;
}
