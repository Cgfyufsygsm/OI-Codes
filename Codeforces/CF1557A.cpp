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

typedef long long ll;
const int maxn = 2e5 + 5;

int t, n;
ll a[maxn], sum[maxn];

int main() {
    read(t);
    while (t--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        std::sort(a + 1, a + n + 1);
        FOR(i, 1, n - 1) sum[i] = sum[i - 1] + a[i];
        printf("%lf\n", a[n] + double(sum[n - 1]) / double(n - 1));
    }
    return 0;
}