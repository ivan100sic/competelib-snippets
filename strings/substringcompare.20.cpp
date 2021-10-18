// Substring comparator

#include <vector>
#include <string>
#include <utility>
#include <compare>

#include <iostream>

using namespace std;

/*snippet-begin*/
struct substring_compare {
    vector<vector<int>> cc;

    int re(int x, int n) { return x >= n ? x - n : x; }

    substring_compare(const string& s) {
        int n = s.size(), sz = 0;
        vector<int> c(begin(s), end(s)), p(n);
        vector<vector<int>> g(max(n, 128));
        for (int i=0; i<n; i++) {
            g[c[i]].push_back(i);
        }
        for (auto& gr : g) {
            for (int i : gr) {
                p[sz++] = i;
            }
            gr.clear();
        }
        for (int h=1; h<n; h*=2) {
            cc.push_back(c);
            vector<int> pn(n), cn(n);
            for (int j : p) {
                int jp = re(j+n-h, n);
                g[c[jp]].push_back(jp);
            }
            sz = 0;
            for (auto& gr : g) {
                for (int i : gr) {
                    pn[sz++] = i;
                }
                gr.clear();
            }
            cn[pn[0]] = 0;
            int nc = 1;
            for (int i=1; i<n; i++) {
                int s0 = pn[i-1], s1 = pn[i];
                if (c[s1] == c[s0] && c[re(s1+h, n)] == c[re(s0+h, n)]) {
                    cn[s1] = nc - 1;
                } else {
                    cn[s1] = nc++;
                }
            }
            swap(c, cn);
            swap(p, pn);
        }
    }

    struct substring {
        substring_compare* ctx;
        int l, r;

        strong_ordering operator<=>(const substring& o) const {
            int tw = r - l, ow = o.r - o.l, tl = l, ol = o.l;
            int w = min(tw, ow);
            for (size_t i=0; i<ctx->cc.size(); i++) {
                if (w & (1 << i)) {
                    int d = ctx->cc[i][tl] - ctx->cc[i][ol];
                    if (d) return d <=> 0; 
                    tl += 1 << i;
                    ol += 1 << i;
                }
            }
            return tw <=> ow;
        }

        bool operator== (const substring& o) const {
            return (*this <=> o) == 0;
        }
    };

    substring operator() (int l, int r) {
        return {this, l, r};
    }
};
/*snippet-end*/

int main() {
    substring_compare c("abcdefabc");

    if (c(0, 3) != c(6, 9)) return 1;
    if (c(0, 3) != c(0, 3)) return 1;
    if (c(0, 3) >= c(3, 6)) return 1;
}
