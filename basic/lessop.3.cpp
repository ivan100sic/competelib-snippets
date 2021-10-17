// Comparison operator

#define SNIPPET_ARG(id, name, x) x

struct something {
    int x;

    /*snippet-begin*/
    bool operator< (const SNIPPET_ARG(1,,something)& o) const {
        SNIPPET_ARG(0,,return x < o.x;)  
    }
    /*snippet-end*/
};

int main() {
    something a, b;
    a.x = 4;
    b.x = 5;

    return !(a < b);  
}
