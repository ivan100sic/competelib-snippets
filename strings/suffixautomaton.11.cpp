// Suffix automaton

#include <vector>
#include <map>
#include <string>
#include <algorithm>
#include <limits>
#include <numeric>
using namespace std;

/*snippet-begin*/
template<class T = char>
struct suffix_automaton {
    struct node {
        map<T, int> next;
        int link, len;
        bool cl;
    };

    vector<node> b;
    vector<int> _topo;

    template<class U>
    suffix_automaton(const U& s) {
        b.push_back({{}, -1, 0, false});
        int last = 0;
        for (T x : s)
            last = extend(x, last);
    }

    node& operator[](int x) {
        return b[x];
    }

    int extend(T x, int last) {
        int curr = b.size();
        b.emplace_back();
        b[curr].len = b[last].len + 1;
        int p = last;
        for (; p != -1 && !b[p].next.count(x); p = b[p].link)
            b[p].next[x] = curr;
        if (p == -1) {
            b[curr].link = 0;
        } else {
            int q = b[p].next[x];
            if (b[p].len + 1 == b[q].len) {
                b[curr].link = q;
            } else {
                int clone = b.size();
                b.emplace_back(b[q]);
                b[clone].len = b[p].len + 1;
                b[clone].cl = true;
                for (; p != -1 && b[p].next[x] == q; p = b[p].link)
                    b[p].next[x] = clone;
                b[curr].link = b[q].link = clone;
            }
        }
        return curr;
    }

    int operator()(int x, T y) {
        if (x == -1) return -1;
        auto it = b[x].next.find(y);
        return it == b[x].next.end() ? -1 : it->second;
    }

    const vector<int>& topo() {
        auto& v = _topo;
        if (!v.size()) {
            v.resize(b.size());
            iota(begin(v), end(v), 0);
            sort(begin(v), end(v), [&](int i, int j) { return b[i].len < b[j].len; });
        }
        return v;
    }

    template<class F, class G>
    auto dp_tree(F f, G g) -> vector<decltype(f(0))> {
        auto& t = topo();
        int n = b.size();
        vector<decltype(f(0))> v(n);
        for (int i=0; i<n; i++)
            v[i] = f(i);
        for (int i=n-1; i; i--) {
            int y = t[i], x = b[y].link;
            v[x] = g(v[x], v[y]);
        }
        return v;
    }

    vector<int> firstpos() {
        return dp_tree(
            [&](int i) { return b[i].cl ? numeric_limits<int>::max() : b[i].len; },
            [](int x, int y) { return min(x, y); });
    }

    vector<int> lastpos() {
        return dp_tree(
            [&](int i) { return b[i].cl ? numeric_limits<int>::max() : b[i].len; },
            [](int x, int y) { return max(x, y); });
    }

    vector<int> endpos_size() {
        return dp_tree([&](int i) { return 1 - b[i].cl; }, plus<int>());
    }
};
/*snippet-end*/

int main() {
    string s("abababc");
    suffix_automaton<char> sa(s);

    int z = sa(sa(0, 'a'), 'b');
    
    return sa.endpos_size()[z] != 3;
}
