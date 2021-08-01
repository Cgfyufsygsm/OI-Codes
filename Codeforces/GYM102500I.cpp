#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 21;
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

const int maxn = 1e6 + 5;
int n, a[maxn], b[maxn];

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]), b[i] = a[i];
    std::sort(b + 1, b + n + 1);
    int l = 1, r = 1;
    FOR(i, 1, n)
        if (a[i] != b[i]) {
            l = i;
            break;
        }
    DEC(i, n, 1)
        if (a[i] != b[i]) {
            r = i;
            break;
        }
    std::reverse(a + l, a + r + 1);
    FOR(i, 1, n)
        if (a[i] != b[i]) return puts("impossible"), 0;
    printf("%d %d\n", l, r);
    return 0;
}