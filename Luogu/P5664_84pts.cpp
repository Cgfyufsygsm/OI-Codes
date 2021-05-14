#include <cstdio>
#include <cctype>
#include <cstring>

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

typedef long long ll;
const int maxn = 100 + 5, maxm = 2000 + 5;
const int mod = 998244353;

int n, m;
ll a[maxn][maxm], s[maxn]; //n 方法，m食材
ll ans = 1;
ll f[maxn][maxn][maxn]; //考虑到第 a 种食材，前 i 种方法，其余做了 j 道菜，剩下 k 道是用当前食材做的

int main()
{
    n = read(), m = read();
    for (int i = 1; i <= n; ++i)
    {
        for (int j = 1; j <= m; ++j)
            a[i][j] = read(), s[i] = (s[i] + a[i][j]) % mod;
        ans = ans * (s[i] + 1) % mod;
    }
    ans = (ans - 1ll) % mod;        //先减掉全部选的方案
    for (int gg = 1; gg <= m; ++gg) //枚举每一种食材
    {
        memset(f, 0, sizeof f);
        f[0][0][0] = 1; //边界
        for (int i = 1; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
                for (int k = 0; k <= n; ++k)
                {
                    if (j + k > i)
                        break;
                    ll tmp1 = 0, tmp2 = 0, tmp3 = 0;
                    tmp1 = f[i - 1][j][k];
                    if (j > 0) //防止访问负下标而 RE
                        tmp2 = f[i - 1][j - 1][k] * (s[i] - a[i][gg]) % mod;
                    if (k > 0) //防止访问负下标而 RE
                        tmp3 = f[i - 1][j][k - 1] * a[i][gg] % mod;
                    f[i][j][k] = tmp1 + tmp2 + tmp3;
                    f[i][j][k] %= mod;
                }
        ll tmp = 0; //记录不合法方案数
        for (int i = 0; i <= n; ++i)
            for (int j = 0; j <= n; ++j)
            {
                ll tot = i + j;
                if (tot > n)
                    break;
                if (j <= (tot >> 1))
                    continue;
                tmp += f[n][i][j], tmp %= mod;
            }
        ans = (ans - tmp + mod) % mod; //取模注意防止负数出现
    }
    printf("%lld\n", ans);
    return 0;
}