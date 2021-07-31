#include <cstdio>
#include <cctype>
#define il inline
#define int unsigned
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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
typedef long long ll;

const int maxn = 5e5 + 5;
int flg[maxn], p[maxn], cntp;
ll f[maxn], ans[maxn];

void init() {
    f[1] = 1;
    FOR(i, 2, maxn - 3)
    {
        if (!flg[i]) p[++cntp] = i, f[i] = 1ll * (i - 1) * i + 1;
        for (int j = 1; j <= cntp && i * p[j] <= maxn - 3; ++j)
        {
            flg[i * p[j]] = 1;
            if (i % p[j] == 0)
            {
                f[i * p[j]] = f[i] + (f[i] - f[i / p[j]]) * p[j] * p[j];
                break;
            }
            f[i * p[j]] = f[i] * f[p[j]];
        }
    }
    FOR(i, 1, maxn - 3) f[i] = ((f[i] + 1) * i) / 2, f[i] += f[i - 1];
    for (ll d = 1; d <= maxn - 3; ++d)
        for (ll i = 1; i * d <= maxn - 3; ++i) {
            ans[d * i] += d * d * f[i];
            if (d * (i + 1) <= maxn - 3)
                ans[d * (i + 1)] -= d * d * f[i];
        }
    FOR(i, 1, maxn - 3) ans[i] += ans[i - 1];
    return;
}

signed main() {
    int T; read(T);
    init();
    FOR(kase, 1, T) {
        int n; read(n);
        printf("Case #%u: %u\n", kase, (unsigned)ans[n]);
    }
    return 0;
}