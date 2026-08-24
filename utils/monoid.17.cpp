// Generic monoid wrapper

#include <optional>
#include <utility>
using namespace std;

/*snippet-begin*/
template<class T>
struct monoid {
    optional<T> v;

    template<class... U>
    monoid(U... v) : v(forward<U>(v)...) {}

    monoid operator+ (const monoid& b) const {
        if (!v) return b;
        if (!b.v) return *this;
        return *v + *b.v;
    }

    monoid& operator+= (const monoid& b) {
        return *this = *this + b;
    }
};
/*snippet-end*/

struct addable {
    int x;
    addable(int x) : x(x) {}
};

addable operator+ (const addable& a, const addable& b) {
    return addable(a.x + b.x);
}

int main() {
    using m = monoid<addable>;

    m a(2), b(3), e;

    if ((a + b).v.value().x != 5) return 1;
    if ((a + e).v.value().x != 2) return 1;
    if ((e + a).v.value().x != 2) return 1;
    if ((e + e).v.has_value()) return 1;

    m c(10);
    if (((a + b) + c).v.value().x != (a + (b + c)).v.value().x) return 1;

    return 0;
}
