// Lexicographically minimum rotation

#include <string>
#include <algorithm>
using namespace std;

template<class S, class F>
void duval(const S& s, F f) {
    int n = s.size();
    for (int l=0; l<n;) {
        int r = l, p = l + 1;
        for (; r < n && s[r] <= s[p]; ++r, ++p) {
            if (s[r] < s[p]) r = l-1;
        }
        while (l <= r) {
            f(l, l+p-r);
            l += p-r;
        }
    }
}

/*snippet-begin*/
template<class S>
int min_rotation(S s) {
    int n = s.size();
    s.resize(2 * n);
    copy_n(s.begin(), n, s.begin() + n);
    int z = 0;
    duval(s, [&](int l, int r) { if (l < n) z = l; });
    return z;
}
/*snippet-end*/

int main() {
    string s = "abbbabb";
    return min_rotation(s) != 4;
}
