// Interactive problems with caching

#include <functional>
#include <string>
#include <sstream>
#include <map>

using std::map;
using std::pair;
using std::endl;
std::ostringstream cout;
std::istringstream cin;

/*snippet-begin*/
template<class I, class O = int>
struct cached_interactive {
    map<I, O> c;

    template<class... T>
    O ask(T... a) {
        I i{a...};
        auto it = c.lower_bound(i);
        if (it == c.end() || i < it->first) {
            cout << '?';
            ((cout << ' ' << a), ...) << endl;
            O o;
            cin >> o;
            c.emplace_hint(it, i, o);
            return o;
        } else {
            return it->second;
        }
    }

    template<class... T>
    void answer(T... a) {
        cout << '!';
        ((cout << ' ' << a), ...) << endl;
    }
};
/*snippet-end*/

int main() {
    cin.str("0 1 2 3 4 5 6 7 8 9 -1 -1 -1");

    cached_interactive<pair<int, int>> ci;
    for (int i=0; i<100; i++) {
        for (int j : {0, 3}) {
            for (int k : {0, 3}) {
                if (ci.ask(j, k) < 0) {
                    return 1;
                }
            }
        }
    }

    // endl could be \r\n
    if (cout.str().size() > 63) {
        return 1;
    }
}
