// Python-like range

/*snippet-begin*/
template<class T>
struct rr {
    struct valit {
        T val;
        valit(T x) : val(x) {}
        T operator* () const { return val; }
        T operator* () { return val; }
        valit& operator++ () {
            ++val;
            return *this;
        }
        bool operator != (const valit& other) const {
            return val != other.val;
        }
    };

    const valit l, r;
    rr(T x) : l(0), r(x) {}
    rr(T x, T y) : l(x), r(y) {}

    valit begin() { return l; }
    valit end() { return r; }
};
/*snippet-end*/

int main() {
    int z = 0;
    for (int x : rr<int>(0, 101)) {
        z += x;
    }

    return z != 5050;
}
