#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 55;
int r, c;

char map[maxn][maxn];

const int maxm = 5005;

int f[maxm][maxm];
int belr[maxn][maxn], belc[maxn][maxn], cntr, cntc;

int match[maxm], vis[maxm], idx;

int dfs(int u)
{
    FOR(v, 1, cntc)
    {
        if (!f[u][v] || vis[v] == idx) continue;
        vis[v] = idx;
        if (!match[v] || dfs(match[v]))
        {
            match[v] = u;
            return 1;
        }
    }
    return 0;
}

int main()
{
    scanf("%d %d", &r, &c);
    FOR(i, 1, r)
        scanf("%s", map[i] + 1);
    FOR(i, 1, r)
    {
        int j = 1;
        while (j <= c)
        {
            while (map[i][j] == '.')
                ++j;
            if (j <= c && map[i][j] == '*')
            {
                ++cntr;
                while (j <= c && map[i][j] == '*')
                    belr[i][j] = cntr, ++j;
            }
        }
    }
    FOR(j, 1, c)
    {
        int i = 1; 
        while (i <= r)
        {
            while (map[i][j] == '.')
                ++i;
            if (i <= r && map[i][j] == '*')
            {
                ++cntc;
                while (i <= r && map[i][j] == '*')
                    belc[i][j] = cntc, ++i;
            }
        }
    }
    FOR(i, 1, r)
        FOR(j, 1, c)
            if (belr[i][j] && belc[i][j])
                f[belr[i][j]][belc[i][j]] = 1;
    int ans = 0;
    FOR(i, 1, cntr)
        ++idx, ans += dfs(i);
    printf("%d\n", ans);
    return 0;
}