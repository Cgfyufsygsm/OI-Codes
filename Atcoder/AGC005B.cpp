#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 200000 + 5;

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

inline ll max(ll a, ll b) {return a > b ? a : b;}
inline ll min(ll a, ll b) {return a < b ? a : b;}

ll n, a[maxn], stk[maxn], top, l[maxn], r[maxn];

int main()
{
    n = read();
    FOR(i, 1, n) a[i] = read(), l[i] = 1, r[i] = n;
    ll ans = 0;
    FOR(i, 1, n)
    {
        while (top && a[stk[top]] >= a[i]) r[stk[top--]] = i - 1;
        l[i] = stk[top] + 1;
        stk[++top] = i;
    }
    FOR(i, 1, n)
        ans += a[i] * (r[i] - i + 1) * (i - l[i] + 1);
    printf("%lld\n", ans);
    return 0;
}