// Pretty debugging

#include <iostream>
#include <tuple>
#include <vector>
#include <string>
using namespace std;

/*snippet-begin*/
namespace debug {
    const char yellow[] = "\x1b[33m";
    const char magenta[] = "\x1b[35m";
    const char blue[] = "\x1b[36m";
    const char green[] = "\x1b[32m";
    const char reset[] = "\x1b[0m";
    const char bold[] = "\x1b[1m";
 
    template<class T, typename std::enable_if_t<
        is_arithmetic_v<T> && !is_same_v<T, char>
        >* = nullptr>
    auto debug(const T& x) -> decltype(cerr << x, 0) {
        return cerr << green << x << reset, 0; 
    }
 
    int debug(const char& x) {
        return cerr << yellow << '\'' << x << '\'' << reset, 0;
    }
 
    int debug(const string& x) {
        return cerr << yellow << '"' << x << '"' << reset, 0;
    }
 
    template<size_t i, class T>
    int debug_tuple(const T& x) {
        constexpr size_t n = tuple_size<T>::value;
        if (i == 0) {
            cerr << '(';
        }
        debug(get<i>(x));
        if constexpr (i == n - 1) {
            cerr << ')';
        } else {
            cerr << ", ";
            debug_tuple<i+1>(x);
        }
        return 0;
    }
 
    template<class T>
    auto debug(const T& x) -> decltype(debug(get<0>(x))) {
        return debug_tuple<0>(x);
    }
 
    template<class T>
    auto debug(const T& x) -> decltype(debug(*x.begin())) {
        cerr << '{';
        auto it = x.begin();
        while (1) {
            if (it == x.end()) {
                cerr << '}';
                return 0;
            } else {
                debug(*it);
                if (next(it) != x.end()) {
                    cerr << ", ";
                }
                ++it;
            }
        }
    }
 
    template<class... T>
    void debug_pack(const T&... x) {
        int k = sizeof...(T), i = 0;
        ((debug(x), cerr << ", "+2*(++i >= k)), ...);
    }
 
    template<class... T>
    void debug_run(int l, const char* n, const T&... x) {
        cerr << magenta << "Line " << l << ": " << blue << bold << n << reset << " = ";
        debug_pack(x...);
        cerr << '\n';
    }
}
 
#ifdef LOCAL
    #define dbg(...) (debug::debug_run(__LINE__, #__VA_ARGS__, __VA_ARGS__))
#else
    #define dbg(...)
#endif
/*snippet-end*/

int main() {
    vector<string> a = {"abc", "def"};
    dbg(a);
    dbg("hello");
    dbg(1.23, 0, 'a');
    dbg(string_view("hello"));
    dbg(tuple(1, 2, "abc"));
}
