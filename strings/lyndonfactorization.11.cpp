// Duval's algorithm (Lyndon factorization)

#include <string>

/*snippet-begin*/
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
/*snippet-end*/

int main() {
    std::string s = "cbcabc";
    int c = 0, ok = 1;
    int a[3] = {0, 1, 3};
    int b[3] = {1, 3, 6};
    duval(s, [&](int l, int r) {
        if (a[c] != l || b[c] != r) {
            ok = 0;
        }
        c++;
    });

    return ok != 1;
}
