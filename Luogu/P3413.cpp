#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1005, mod = 1e9 + 7;

int num[maxn], f[maxn][15][15][2][2][2];

int dfs(int pos, int last1, int last2, bool valid, bool lim, bool zero)
{
    if (!pos) return valid;
    if (~f[pos][last1][last2][valid][lim][zero]) return f[pos][last1][last2][valid][lim][zero];
    int ret = 0;
    FOR(i, 0, 9)
    {
        if (lim && i > num[pos]) break;
        (ret += dfs(pos - 1, i, zero ? -1 : last1, valid || ((i == last1 || i == last2) && !(zero && i == 0)), lim && i == num[pos], zero && i == 0)) %= mod;
    }
    return f[pos][last1][last2][valid][lim][zero] = ret;
}

int solve(char *s)
{
    int len = 0;
    for (int i = strlen(s) - 1; i >= 0; --i) num[++len] = s[i] - '0';
    memset(f, -1, sizeof f);
    return dfs(len, -1, -1, 0, 1, 1);
}

int check(char *s)
{
    for (int i = 0, last1 = -1, last2 = -2; s[i]; last2 = last1, last1 = s[i] - '0', ++i)
        if (s[i] - '0' == last1 || s[i] - '0' == last2) return 1;
    return 0;
}

int main()
{
    char l[maxn], r[maxn];
    scanf("%s %s", l, r);
    printf("%d\n", (solve(r) - solve(l) + check(l) + mod) % mod);
    return 0;
}