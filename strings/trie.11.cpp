// Trie

#include <vector>
#include <map>
#include <functional>
#include <string>
using namespace std;

/*snippet-begin*/
template<class C = char, class T = int, class F = plus<T>>
struct trie {
    struct node : map<C, int> {
        T t, s;
        node() : t(T()), s(T()) {}
    };

    vector<node> a;
    F f;
    
    trie(F f = {}) : a(1), f(f) {}

    template<class V>
    int add(const V& b, const T& t) {
        int x = 0;
        for (C c : b) {
            a[x].s = f(a[x].s, t);
            int& p = a[x][c];
            if (!p) {
                x = p = a.size();
                a.emplace_back();
            } else {
                x = p;
            }
        }
        a[x].s = f(a[x].s, t);
        a[x].t = f(a[x].t, t);
        return x;
    }

    int operator() (int x, const T& c) const {
        auto it = a[x].find(c);
        return it == a[x].end() ? 0 : it->second;
    }

    const node& operator[](int x) const {
        return a[x];
    }
};
/*snippet-end*/

int main() {
    trie<char, int, plus<int>> t;
    t.add(string("abc"), 10);
    t.add(string("abd"), 15);

    return t[t(t(0, 'a'), 'b')].s != 25;
}
