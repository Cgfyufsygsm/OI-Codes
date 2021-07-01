#include <cstdio>
#include <cctype>
#include <cstring>
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

const int maxn = 1e5 + 5, maxk = 205;
typedef long long ll;

ll s[maxn], f[maxn], g[maxn], n, k;
int fa[maxn][maxk];

il ll X(int i) {return -s[i];}
il ll Y(int i) {return g[i] - s[i] * s[i];}

int main()
{
    n = read(), k = read();
    FOR(i, 1, n) s[i] = s[i - 1] + read();
    static int q[maxn], head, tail;
    FOR(t, 1, k)
    {
        memcpy(g, f, sizeof f);
        q[head = tail = 1] = 0;
        FOR(i, 1, n)
        {
            while (head < tail && (Y(q[head]) - Y(q[head + 1])) <= s[i] * (X(q[head]) - X(q[head + 1]))) ++head;
            int &j = q[head];
            fa[i][t] = j;
            f[i] = g[j] + s[i] * s[j] - s[j] * s[j];
            while (head < tail && (Y(q[tail - 1]) - Y(q[tail])) * (X(q[tail]) - X(i)) >= (Y(q[tail]) - Y(i)) * (X(q[tail - 1]) - X(q[tail]))) --tail;
            q[++tail] = i;
        }
    }
    printf("%lld\n", f[n]);
    for (int x = fa[n][k]; k; x = fa[x][--k]) printf("%d ", x);
    return 0;
}