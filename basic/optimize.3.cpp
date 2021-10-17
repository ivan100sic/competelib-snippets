// Try to optimize compiler for speed

#if XYZ
/*snippet-begin*/
#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#pragma GCC target("sse,sse2,sse3,ssse3,sse4,popcnt,abm,mmx,avx,tune=native")
#endif
/*snippet-end*/
#endif

int main() {
    return 0;
}
