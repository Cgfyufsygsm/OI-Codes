#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 3005;

typedef long long ll;

ll read()
{
    ll s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}


ll sum[maxn], a[maxn];
ll f[maxn][maxn];
int n;

const ll mod = 1e9 + 7;

//f[i][j] : i 组，且这些元素模 i 的余数为 j

int main()
{
    n = read();
    FOR(i, 1, n) a[i] = read(), sum[i] = a[i] + sum[i -1];
    f[1][0] = 1;
    ll ans = 0;
    FOR(i, 1, n)
    {
        DEC(j, n, 1)
        {
            f[j + 1][sum[i] % (j + 1)] += f[j][sum[i] % j];
            f[j + 1][sum[i] % (j + 1)] %= mod;
            if (i == n)
                (ans += f[j][sum[i] % j]) %= mod; 
        }
    }
    printf("%lld\n", ans);
    return 0;
}