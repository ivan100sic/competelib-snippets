// Variations with repetitions
#include <vector>
#include <tuple>
using namespace std;

/*snippet-begin*/
template<class T = int>
struct variations {
    struct iterator {
        T l, h;
        vector<T> a;
    
        const vector<T>& operator* () const { return a; }
        bool operator== (const iterator& b) const { return tie(l, h, a) == tie(b.l, b.h, b.a); }
        bool operator!= (const iterator& b) const { return !(*this == b); }
        iterator& operator++ () {
            int i = (int)a.size() - 1;
            a[i]++;
            while (i && a[i] > h) {
                a[i] = l;
                a[--i]++;
            }
            return *this;
        }
    };

    int n, k; T l;
    variations(int n, int k, T l = 0) : n(n), k(k), l(l) {}

    iterator begin() {
        return {l, l+k-1, vector<T>(n, l)};
    }

    iterator end() {
        vector<T> e(n, l);
        e[0] = l+k;
        return {l, l+k-1, move(e)};
    }
};
/*snippet-end*/

int main() {
    variations<> v(2,3,1);

    int ind = 0;
    vector<vector<int>> a = {{1,1},{1,2},{1,3},{2,1},{2,2},{2,3},{3,1},{3,2},{3,3}};
    for (auto it = v.begin(); it != v.end(); ++it){
        if (*it != a[ind]) return 1;
        ++ind;
    }

    return (ind != (int)a.size());
}
