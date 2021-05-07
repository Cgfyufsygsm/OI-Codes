#include <cstdio>
#include <cctype>
#include <map>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5;

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

int n, w[maxn], p;

int getPhi(int n)
{
    int ans = n;
    for (int i = 2; i * i <= n; ++i)
        if (n % i == 0)
        {
            ans = ans / i * (i - 1);
            while (n % i == 0) n /= i;
        }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

int f[maxn << 2];

std::map<int, int> phi;

typedef long long ll;

int qpow(ll a, ll b, ll p)
{
    ll ret = 1;
    for (; b; b >>= 1)
    {
        if (b & 1) ret *= a, ret = (ret >= p ? ret % p + p : ret);
        a *= a;
        if (a >= p) a %= p, a += p;
    }
    return ret;
}

int dfs(int l, int r, int p)
{
    if (l == r || p == 1) return w[l] >= p ? w[l] % p + p : w[l];
    return qpow(w[l], dfs(l + 1, r, phi[p]), p);
}

int main()
{
    n = read(), p = read();
    FOR(i, 1, n) w[i] = read();
    int now = p;
    while (now != 1)
        phi[now] = getPhi(now), now = phi[now];
    phi[now] = 1;
    int q = read();
    while (q--)
    {
        int l = read(), r = read();
        printf("%d\n", dfs(l, r, p) % p);
    }
    return 0;
}