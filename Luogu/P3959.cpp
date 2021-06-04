#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 13, maxm = 1e3 + 5;

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

inline int min(int a, int b) {return a < b ? a : b;}

int e[maxn][maxn], n;
int g[1 << maxn][1 << maxn], f[1 << maxn][maxn], nxt[1 << maxn], lg[1 << maxn];

int main()
{
    memset(e, 0x3f, sizeof e), memset(f, 0x3f, sizeof f);
    n = read();
    FOR(i, 1, n - 1) lg[1 << i] = i;
    int m = read();
    while (m--)
    {
        int u = read(), v = read(), w = read();
        if (e[u][v] > w) e[u][v] = e[v][u] = w;
    }


    FOR(i, 1, (1 << n) - 1)
    {
        int v = 0;
        for (int s = ((1 << n) - 1) ^ i, j = s; j; j = (j - 1) & s)
            nxt[j] = v, v = j;
        for (int j = v; j; j = nxt[j])
        {
            int x = lg[j & -j] + 1, v = 3e6 + 5;
            FOR(y, 1, n)
                if ((1 << (y - 1)) & i) v = min(v, e[x][y]);
            g[i][j] = g[i][j ^ (j & -j)] + v;
        }
    }

    FOR(i, 1, n) f[1 << (i - 1)][0] = 0;
    FOR(l, 1, n - 1)
        FOR(i, 1, (1 << n) - 1)
            for (int j = i; j; j = (j - 1) & i)
                f[i][l] = min(f[i][l], f[i ^ j][l - 1] + g[i ^ j][j] * l);
    int ans = 0x3f3f3f3f;
    FOR(l, 0, n) ans = min(ans, f[(1 << n) - 1][l]);
    printf("%d\n", ans);
    return 0;
}