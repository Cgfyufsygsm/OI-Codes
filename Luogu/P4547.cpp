#include <cstdio>
#include <cctype>
#include <map>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO
{
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
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
}

using namespace fastIO;

typedef long long ll;
const int maxn = 16, mod = 1e9 + 7;
const ll inv2 = 500000004, inv4 = 250000002;

struct node
{
    ll S, w;
} tmp, a[maxn << 1][maxn * maxn];

int cnt[maxn << 1], n, m;
std::map<ll, ll> f[1 << maxn];
ll pow[maxn << 1];

void add()
{
    FOR(i, 1, n)
        if (pow[i] & tmp.S)
        {
            a[i][++cnt[i]] = tmp;
            return;
        }
}

ll dp(ll S)
{
    int s = S & ((1 << n) - 1), t = S >> n;

    if (!S) return 1;
    if (f[s].count(t)) return f[s][t];
    ll ans = 0;

    int pos = 0;
    FOR(i, 1, n) if (S & pow[i]) {pos = i; break;}
    FOR(i, 1, cnt[pos])
        if ((S & a[pos][i].S) == a[pos][i].S)
            ans = (ans + dp(S ^ a[pos][i].S) * a[pos][i].w % mod) % mod;
    return f[s][t] = ans;
}

int main()
{
    n = read(), m = read();
    pow[1] = 1;
    FOR(i, 2, n << 1) pow[i] = pow[i - 1] << 1;
    while (m--)
    {
        int op = read();
        if (!op)
        {
            int u = read(), v = read();
            tmp.S = pow[u] | pow[v + n], tmp.w = inv2;
            add();
        }
        else
        {
            int u1 = read(), v1 = read(), u2 = read(), v2 = read();
            ll S1 = pow[u1] | pow[v1 + n], S2 = pow[u2] | pow[v2 + n];
            tmp.S = S1, tmp.w = inv2, add();
            tmp.S = S2, add();

            if (S1 & S2) continue;
            
            tmp.S = S1 | S2, tmp.w = (op == 1 ? inv4 : mod - inv4), add();
        }
    }
    ll ans = 0;
    ans = dp((1ll << (2 * n)) - 1) * pow[n + 1] % mod;
    printf("%lld\n", ans);
    return 0;
}