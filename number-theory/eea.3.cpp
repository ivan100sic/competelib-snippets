// Extended Euclidean Algorithm

/*snippet-begin*/
template<class T>
T eea(T a, T b, T& x, T& y) {
    if (!b) {
        x = 1;
        y = 0;
        return a;
    }

    T x1, y1;
    T g = eea(b, a % b, x1, y1);
    x = y1;
    y = x1 - (a / b) * y1;
    return g;
}
/*snippet-end*/

int main() {
    int a = 10, b = 6, x, y;
    int g = eea(a, b, x, y);
    return g != 2 || a*x + b*y != g;
}
