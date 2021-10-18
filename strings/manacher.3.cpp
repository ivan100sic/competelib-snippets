// Manacher's algorithm (palindromes)

#include <vector>
#include <string>
#include <algorithm>

#include <iostream>

using namespace std;

/*snippet-begin*/
// ab(c)ba, odd -> 2
// ab(c)cba, even -> 2
// (x)y, even -> -1
template<bool odd, class S>
vector<int> manacher(const S& s) {
    int g = odd ? 0 : 1;
    int n = s.size();
    vector<int> z(n-g);
    for (int i=0, l=0, r=-1; i<n-g; i++) {
        if (i+g <= r) z[i] = max(-1, min(z[l+r-i-g], min(i-l, r-i-g)));
        while (i >= z[i] && i+z[i]+g < n && s[i-z[i]] == s[i+z[i]+g]) z[i]++;
        z[i]--;
        if (i+z[i]+g > r) l = i-z[i], r=i+z[i]+g;
    }
    return z;
}
/*snippet-end*/

int main() {
    string s1 = "abacaba";
    string s2 = "abcddcbaabba";

    vector<int> m1 = manacher<true>(s1);
    vector<int> m2 = manacher<false>(s2);

    if (m1[3] != 3) return 1;
    if (m2[3] != 3) return 1;
}
