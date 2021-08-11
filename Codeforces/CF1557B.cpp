#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 23;
    char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
    il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
    template<typename T> void read(T &n) {
        int x = 0; n = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            n = n * 10 + c - '0', c = getchar();
        n = x ? -n : n;
    }
}

using namespace fastIO;

const int maxn = 1e5 + 5;

int t, n, k;
int a[maxn], aa[maxn];

int main() {
    read(t);
    while (t--) {
        read(n), read(k);
        FOR(i, 1, n) read(a[i]), aa[i] = a[i];
        std::sort(aa + 1, aa + n + 1);
        FOR(i, 1, n) a[i] = std::lower_bound(aa + 1, aa + n + 1, a[i]) - aa;
        int p = 1;
        FOR(i, 2, n) p += (a[i] != a[i - 1] + 1);
        if (p <= k) puts("Yes");
        else puts("No");
    }
    return 0;
}