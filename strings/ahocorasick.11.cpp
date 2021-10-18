// Aho-Corasick automaton

#include <map>
#include <vector>
#include <string>
#include <utility>
using namespace std;

/*snippet-begin*/
struct ahocorasick {
    struct node {
        map<char, int> next, hop;
        int link{0};
    };
    vector<node> b;
    bool done;
    ahocorasick() : b(1), done(false) {}
    int size() const { return b.size(); }

    int operator+= (const string& s) {
        int y = 0;
        for (char x : s) {
            auto it = b[y].next.find(x);
            if (it == b[y].next.end()) {
                it = b[y].next.insert(it, {x, b.size()});
                b.emplace_back();
            }
            y = it->second;
        }
        done = false;
        return y;
    }

    void bfs() {
        b[0].link = -1;
        vector<int> q(b.size());
        size_t qs = 0, qe = 1;
        while (qs != qe) {
            int x = q[qs++];
            for (auto cy : b[x].next) {
                char c = cy.first;
                int y = cy.second;
                int t = b[x].link;
                while (t != -1 && !b[t].next.count(c))
                    t = b[t].link;
                b[y].link = t != -1 ? b[t].next[c] : 0;
                q[qe++] = y;
            }
        }
        done = true;
    }

    int operator() (int x, char c) {
        if (!done) bfs();
        auto it = b[x].hop.find(c);
        if (it == b[x].hop.end()) {
            int t = x;
            while (t >= 0 && b[t].next.count(c) == 0)
                t = b[t].link;
            it = b[x].hop.insert(it, {c, t == -1 ? 0 : b[t].next[c]});
        }
        return it->second;
    }
};
/*snippet-end*/

int main() {
    ahocorasick ac;
    ac += "abc";
    ac += "abd";

    int z = 0;
    for (char c : string("abd")) z = ac(z, c);

    return z != 4;
}
