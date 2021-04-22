#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 3e5 + 5;

int n, f[maxn][2][2];
char s[2][maxn];

inline int max(int a, int b) {return a > b ? a : b;}

int dfs(int i, int type, int fa)
{
    if (f[i][type][fa]) return f[i][type][fa];
    f[i][type][fa] = 1;
    if (i > 0 && s[type][i] == 'L' && fa != 0)
        f[i][type][fa] = max(f[i][type][fa], f[i][type][fa] + dfs(i - 1, type ^ 1, 1));
    if (i < n && s[type][i + 1] == 'R' && fa != 1)
        f[i][type][fa] = max(f[i][type][fa], f[i][type][fa] + dfs(i + 1, type ^ 1, 0));
    return f[i][type][fa];
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        memset(f, 0, sizeof f);
        scanf("%d", &n);
        scanf("%s", &s[0][1]);
        FOR(i, 1, n)
            if (s[0][i] == 'L') s[1][i] = 'R';
            else s[1][i] = 'L';
        FOR(i, 0, n)
        {
            dfs(i, 0, 0);
            dfs(i, 0, 1);
            printf("%d ", f[i][0][0] + f[i][0][1] - 1);
        }
        printf("\n");
    }
    return 0;
}