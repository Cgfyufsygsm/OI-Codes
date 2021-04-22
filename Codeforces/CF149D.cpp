#include <cstdio>
#include <cstring>
#define R register
#define FOR(i, a, b) for (R signed i = a; i <= b; ++i)
#define int long long

const int mod = 1000000007, maxn = 1005;
char s[maxn];
int n, f[maxn][maxn][3][3];
int stk[maxn], top, pos[maxn];

#define f(l, r, k1, k2) f[l][r][k1][k2]

void dfs(int l, int r)
{
    if (r == l + 1)
    {
        f(l, r, 0, 1) = f(l, r, 0, 2) = f(l, r, 1, 0) = f(l, r, 2, 0) = 1;
        return;
    }
    if (pos[l] == r)
    {
        dfs(l + 1, r - 1);
        FOR(i, 0, 2)
            FOR(j, 0, 2)
            {
                if (i != 1)
                    f(l, r, 1, 0) = (f(l, r, 1, 0) + f(l + 1, r - 1, i, j)) % mod;
                if (i != 2)
                    f(l, r, 2, 0) = (f(l, r, 2, 0) + f(l + 1, r - 1, i, j)) % mod;
                if (j != 1)
                    f(l, r, 0, 1) = (f(l, r, 0, 1) + f(l + 1, r - 1, i, j)) % mod;
                if (j != 2)
                    f(l, r, 0, 2) = (f(l, r, 0, 2) + f(l + 1, r - 1, i, j)) % mod;
            }
        return;
    }
    else
    {
        dfs(l, pos[l]); dfs(pos[l] + 1, r);
        FOR(i, 0, 2)
            FOR(j, 0, 2)
                FOR(k1, 0, 2)
                    FOR(k2, 0, 2)
                        if (j != k1 || (j == k1 && j == 0))
                            f(l, r, i, k2) += f(l, pos[l], i, j) * f(pos[l] + 1, r, k1, k2) % mod, f(l, r, i, k2) %= mod;
        return;                            
    }
}

signed main()
{
    scanf("%s", s + 1);
    n = strlen(s + 1);
    FOR(i, 1, n)
    {
        if (s[i] == '(')
            stk[++top] = i;
        else
        {
            pos[i] = stk[top];
            pos[stk[top--]] = i;
        }
    }
    dfs(1, n);
    int ans = 0;
    FOR(i, 0, 2)
        FOR(j, 0, 2)
            ans = (ans + f[1][n][i][j]) % mod;
    printf("%lld\n", ans); 
    return 0;
}