// Bidirectional sum

#include <functional>
#include <string>
using namespace std;

/*snippet-begin*/
template<class T, class F = plus<T>>
struct bidirectional_sum {
    T f, b;
    bidirectional_sum(T x = T()) : f(x), b(x) {}
    bidirectional_sum(T&& f, T&& b) : f(f), b(b) {}
    bidirectional_sum operator+ (const bidirectional_sum& o) const {
        return {F()(f, o.f), F()(o.b, b)};
    }
};
/*snippet-end*/

int main() {
    bidirectional_sum<string> a("a"), b("b"), c("c");
    auto d = a + b + c;
    return d.f != "abc" || d.b != "cba";
}
