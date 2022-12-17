// Treap

#include <vector>
#include <functional>
#include <random>
#include <chrono>
using namespace std;

/*snippet-begin*/
template<class T>
struct treap {
    struct node : T {
        unsigned p;
        int l, r;
        
        template<class... A>
        node(A&&... a) : T(forward<A>(a)...) {}
    };

    ranlux48 re;
    vector<node> b;

    treap() : re(chrono::high_resolution_clock::now().time_since_epoch().count()) {}
    
    template<class... A>
    int create(A&&... a) {
        b.emplace_back(forward<A>(a)...);
        b.back().l = b.back().r = -1;
        b.back().p = re();
        return b.size() - 1;
    }

    void enter(int x) {
        if (x != -1) b[x].enter(b, x);
    }

    void pull(int x) {
        b[x].pull(b, x);
    }

    int join(int x, int y) {
        enter(x); enter(y);
        if (x == -1) return y;
        if (y == -1) return x;
        if (b[x].p > b[y].p) {
            b[y].l = join(x, b[y].l);
            pull(y);
            return y;
        } else {
            b[x].r = join(b[x].r, y);
            pull(x);
            return x;
        }
    }

    template<class S>
    pair<int, int> split(int x, S&& s) {
        enter(x);
        if (x == -1) return {-1, -1};
        if (s(b, x)) {
            int y, z;
            tie(y, z) = split(b[x].r, s);
            b[x].r = y;
            pull(x);
            return {x, z};
        } else {
            int y, z;
            tie(y, z) = split(b[x].l, s);
            b[x].l = z;
            pull(x);
            return {y, x};
        }
    }

    template<class E>
    void enumerate(int x, E&& e) {
        if (x == -1) return;
        enter(x);
        enumerate(b[x].l, e);
        e(b, x);
        enumerate(b[x].r, e);
    }

    // Splits using sl first, then sr on the right piece
    template<class F, class SL, class SR>
    int run(int x, SL&& sl, SR&& sr, F&& f) {
        int p, q, r, s;
        tie(p, q) = split(x, sl);
        tie(r, s) = split(q, sr);
        f(b, r);
        return join(p, join(r, s));
    }

    template<class S, class... A>
    int emplace(int x, S&& s, A&&... a) {
        int y = create(forward<A>(a)...);
        int p, q;
        tie(p, q) = split(x, s);
        return join(p, join(y, q));
    }
};

// Inherit to implement sum of subtree trait
template<class T>
struct treap_sum {
    T m_sum_root;
    T m_sum_total;

    template<class N>
    void pull(vector<N>& a, int x) {
        m_sum_total = a[x].l == -1 ? a[x].m_sum_root : a[a[x].l].m_sum_total + a[x].m_sum_root;
        if (a[x].r != -1) m_sum_total = m_sum_total + a[a[x].r].m_sum_total;
    }

    struct splitter {
        T s;

        splitter(T s) : s(s) {}

        template<class N>
        bool operator() (vector<N>& a, int x) {
            T w = a[x].l == -1 ? a[x].m_sum_root : a[a[x].l].m_sum_total + a[x].m_sum_root;
            return s >= w ? (s -= w, true) : false;
        }
    };
};

// Inherit to implement simple data storage trait
template<class T>
struct treap_data {
    T m_data;
};

// Inherit to implement single-element lazy updates trait
template<class T>
struct treap_update {
    T m_update;

    treap_update(T u = T()) : m_update(u) {}

    template<class N>
    void enter(vector<N>& a, int x) {
        N& n = a[x];
        n.m_data = n.m_data + m_update;
        if (n.l != -1) a[n.l].m_update = a[n.l].m_update + n.m_update;
        if (n.r != -1) a[n.r].m_update = a[n.r].m_update + n.m_update;
        n.m_update = T();
    }
};

template<class T, class F = less<T>>
struct treap_compare_splitter {
    T v; F f;
    treap_compare_splitter(const T& v, F f = {}) : v(v), f(f) {}

    template<class N>
    bool operator() (vector<N>& a, int x) {
        return f(a[x].m_data, v);
    }
};

// Inherit to implement reverse trait
struct treap_reverser {
    bool m_reversed;

    template<class N>
    void enter(vector<N>& a, int x) {
        N& n = a[x];
        if (n.m_reversed) {
            swap(n.l, n.r);
            if (n.l != -1) a[n.l].m_reversed ^= 1;
            if (n.r != -1) a[n.r].m_reversed ^= 1;
        }
        n.m_reversed = false;
    }

    struct runner {
        template<class N>
        void operator() (vector<N>& a, int x) {
            if (x != -1) a[x].m_reversed ^= 1;
        }
    };
};

// Inherit to implement size trait
struct treap_size {
    int m_size;

    treap_size() : m_size(1) {}

    template<class N>
    void pull(vector<N>& a, int x) {
        m_size = 1;
        if (a[x].l != -1) m_size += a[a[x].l].m_size;
        if (a[x].r != -1) m_size += a[a[x].r].m_size;
    }

    struct splitter {
        int s;

        splitter(int s) : s(s) {}

        template<class N>
        bool operator() (vector<N>& a, int x) {
            int w = 1;
            if (a[x].l != -1) w += a[a[x].l].m_size;
            return s >= w ? (s -= w, true) : false;
        }
    };
};

// Implement your treap policy here 
struct treap_policy : treap_size, treap_sum<int> {
    treap_policy(int x) {
        m_sum_root = m_sum_total = x;
    }

    template<class N>
    void enter(vector<N>& a, int x) {

    }

    template<class N>
    void pull(vector<N>& a, int x) {
        treap_size::pull(a, x);
        treap_sum::pull(a, x);
    }
};
/*snippet-end*/

int main() {
    treap<treap_policy> tr;
    int a = tr.create(1);
    int b = tr.create(2);
    int c = tr.create(4);
    int root = tr.join(tr.join(a, b), c);
    int sum = 0;
    root = tr.run(root, treap_size::splitter(0), treap_size::splitter(2), [&](const vector<treap<treap_policy>::node>& b, int nd) {
        sum = b[nd].m_sum_total;
    });

    return sum != 3;
}
