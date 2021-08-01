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
using namespace std;

const int maxn = 2e5 + 5;
int n, m;
int a[maxn], b[maxn];
int ans = 1e9 + 7;

int main() {
    read(n), read(m);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, m) read(b[i]);
    std::sort(b + 1, b + m + 1);

    FOR(i, 1, n) {
        int l = 1, r = m, p = 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (b[mid] <= a[i]) p = mid, l = mid + 1;
            else r = mid - 1;
        }
        ans = min(ans, abs(b[p] - a[i]));
        if (p < m) ans = min(ans, abs(b[p + 1] - a[i]));
    }
    printf("%d\n", ans);
    return 0;
}