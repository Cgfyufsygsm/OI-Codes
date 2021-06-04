#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 20;

int w, c[maxn], n;

int f[1 << maxn];//f[s] 状态 s 下的奶牛的最小分组
int g[1 << maxn];//满足 f[s] 状态下剩余的最小重量

inline int max(int a, int b) {return a > b ? a : b;}

int main()
{
    scanf("%d %d", &n, &w);
    FOR(i, 1, n) scanf("%d", c + i);
    memset(f, 0x3f, sizeof f);
    f[0] = 1, g[0] = w;
    FOR(S, 1, (1 << n) - 1)
    {
        FOR(j, 1, n)
            if ((1 << (j - 1)) & S)
            {
                int S0 = S ^ (1 << (j - 1));
                int k = (g[S0] < c[j]);
                if (f[S] > f[S0] + k)
                    f[S] = f[S0] + k, g[S] = k ? w - c[j] : g[S0] - c[j];
                else if (f[S] == f[S0] + k)
                    g[S] = max(g[S], k ? w - c[j] : g[S0] - c[j]);
            }
    }
    printf("%d\n", f[(1 << n) - 1]);
    return 0;
}