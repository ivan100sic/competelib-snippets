// Range Add Sum

#include <functional>
using namespace std;

template<class A, class B, class C, class T>
int segtreelazy(int n, A a, B b, C c, T, int, T) {
    return n;
}

/*snippet-begin*/
template<class T = int>
decltype(auto) range_add_sum(int n) {
    struct node {
        T s; int l;
        node operator+ (const node& b) const { return {s + b.s, l + b.l}; }
        T operator() () const { return s; }
    };
    return segtreelazy(n, plus<node>(), plus<T>(), [](node n, T v) {
        return node{n.s + v * n.l, n.l}; }, node{T(), 0}, T(), node{T(), 1});
}
/*snippet-end*/

int main() {
    return range_add_sum<int>(5) != 5;
}
