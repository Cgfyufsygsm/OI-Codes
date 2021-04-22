#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 255;
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

ll n, minw, w[maxn], t[maxn];
ll f[1005];

inline ll max(ll a, ll b) {return a > b ? a : b;}
inline ll min(ll a, ll b) {return a < b ? a : b;}

bool check(ll mid)
{
    memset(f, 0x80, sizeof f);
    f[0] = 0;
    ll inf = f[minw];
    FOR(i, 1, n)
    {
        ll val = t[i] - w[i] * mid;
        DEC(j, minw, 0)
            if (f[j] != inf)
                f[min(minw, j + w[i])] = max(f[min(minw, j + w[i])], f[j] + val);
    }
    return f[minw] >= 0;
}

int main()
{
    n = read(), minw = read();
    ll l = 0, r = 0, ans;
    FOR(i, 1, n)
        w[i] = read(), t[i] = read() * 1000, r += t[i];
    while (l <= r)
    {
        ll mid = l + r >> 1;
        check(mid) ? l = mid + 1, ans = mid : r = mid - 1;
    }
    printf("%lld\n", ans);
    return 0;
}