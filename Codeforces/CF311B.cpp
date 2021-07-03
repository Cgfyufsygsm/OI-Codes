#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO
{
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read()
    {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

typedef long long ll;
const int maxn = 1e5 + 5;

int n, m, p;
ll d[maxn], t[maxn], s[maxn];

ll f[maxn], g[maxn];//f[i][j] 前 i 只猫猫用 j 个铲屎官都搞定了的最小时间花费

int q[maxn], head, tail;

il ll X(int i) {return i;}
il ll Y(int i) {return g[i] + s[i];}
il ll min(ll a, ll b) {return a < b ? a : b;}

int main()
{
    n = read(), m = read(), p = read();
    FOR(i, 2, n) d[i] = d[i - 1] + read();
    FOR(i, 1, m)
    {
        ll h = read();
        t[i] = read() - d[h];
    }
    std::sort(t + 1, t + m + 1);
    FOR(i, 1, m) s[i] = s[i - 1] + t[i];
    memset(f, 0x3f, sizeof f);
    f[0] = 0;
    FOR(k, 1, p)
    {
        memcpy(g, f, sizeof f);
        q[head = tail = 1] = 0;
        FOR(i, 1, m)
        {
            int k = t[i];
            while (head < tail && (Y(q[head + 1]) - Y(q[head])) <= k * (X(q[head + 1]) - X(q[head]))) ++head;
            int j = q[head];
            f[i] = g[j] - t[i] * j + s[j] + i * t[i] - s[i];
            while (head < tail && (Y(q[tail]) - Y(q[tail - 1])) * (X(i) - X(q[tail])) >= (Y(i) - Y(q[tail])) * (X(q[tail]) - X(q[tail - 1]))) --tail;
            q[++tail] = i;
        }
    }
    printf("%lld\n", f[m]);
    return 0;
}