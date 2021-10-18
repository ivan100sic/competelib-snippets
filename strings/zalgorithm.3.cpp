// Z-Algorithm (Strings)

#include <vector>
#include <string>
#include <algorithm>
using namespace std;

/*snippet-begin*/
template<class V>
vector<int> z_algorithm(const V& v) {
    int n = v.size();
    vector<int> z(n);
    for (int i=1, l=0, r=0; i<n; i++) {
        if (i < r) z[i] = min(z[i-l], r-i);
        while (i + z[i] < n && v[i + z[i]] == v[z[i]]) z[i]++;
        if (i + z[i] > r) l = i, r = i + z[i];
    }
    return z;
}
/*snippet-end*/

int main() {
    string s = "ababc";
    return z_algorithm(s)[2] != 2;
}
