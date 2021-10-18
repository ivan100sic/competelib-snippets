// Prefix function (KMP)

#include <vector>
#include <string>
using namespace std;

/*snippet-begin*/
template<class V>
vector<int> prefix_function(const V& v) {
    int n = v.size();
    vector<int> f(n+1);
    f[0] = -1;
    for (int i=1; i<=n; i++) {
        int r = f[i-1];
        while (r != -1 && v[r] != v[i-1]) r = f[r];
        f[i] = r+1;
    }
    return f;
}
/*snippet-end*/

int main() {
    string s = "ababc";
    return prefix_function(s)[3] != 1;
}
