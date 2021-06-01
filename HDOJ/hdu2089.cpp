#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int num[10];
int f[10][10][2];

int dfs(int pos, int last, int lim)
{
    if (!pos) return 1;
    if (~f[pos][last][lim]) return f[pos][last][lim];
    int ret = 0;
    FOR(i, 0, 9)
    {
        if (lim && i > num[pos]) break;
        if (i == 4 || (i == 2 && last == 6)) continue;
        ret += dfs(pos - 1, i, lim && i == num[pos]);
    }
    return f[pos][last][lim] = ret;
}

int solve(int n)
{
    if (n < 0) return 0;
    if (n == 0) return 1;
    int len = 0;
    while (n) num[++len] = n % 10, n /= 10;
    memset(f, -1, sizeof f);
    return dfs(len, -1, 1);
}

int main()
{
    int l, r;
    while (scanf("%d %d", &l, &r) != EOF && l && r)
        printf("%d\n", solve(r) - solve(l - 1));
    return 0;
}