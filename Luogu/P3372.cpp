#include <cstdio>
#include <cctype>
#define L (k << 1)
#define R (L | 1)
#define mid (i + j >> 1)
typedef long long ll;
using namespace std;

const int maxn = 1e5 + 5;
int n, m;
ll f[maxn << 2], tag[maxn << 2];

inline ll read()
{
    bool w = 0;
    ll x = 0;
    char c = getchar();
    while (!isdigit(c))
    {
        if (c == '-')
            w = 1;
        c = getchar();
    }
    while (isdigit(c))
        x = x * 10 + c - '0', c = getchar();
    return w ? -x : x;
}

void build(int i, int j, int k)
{
    if (i == j)
    {
        f[k] = read();
        return;
    }
    build(i, mid, L);
    build(mid + 1, j, R);
    f[k] = f[L] + f[R];
    return;
}

void down(int i, int j, int k)
{
    f[L] += (mid - i + 1ll) * tag[k];
    f[R] += (j - mid) * tag[k];
    tag[L] += tag[k], tag[R] += tag[k];
    tag[k] = 0;
    return;
}

void modify(int i, int j, int x, int y, int k, ll d)
{
    if (x <= i && y >= j)
    {
        f[k] += d * (j - i + 1ll), tag[k] += d;
        return;
    }
    if (tag[k])
        down(i, j, k);
    if (x <= mid)
        modify(i, mid, x, y, L, d);
    if (y > mid)
        modify(mid + 1, j, x, y, R, d);
    f[k] = f[L] + f[R];
    return;
}

ll ask(int i, int j, int x, int y, int k)
{
    if (x <= i && y >= j)
        return f[k];
    if (tag[k])
        down(i, j, k);
    ll ans = 0;
    if (x <= mid)
        ans += ask(i, mid, x, y, L);
    if (y > mid)
        ans += ask(mid + 1, j, x, y, R);
    return ans;
}

int main()
{
    n = read(), m = read();
    build(1, n, 1);
    int c, x, y;
    ll k;
    while (m--)
    {
        c = read(), x = read(), y = read();
        if (c == 1)
        {
            k = read();
            modify(1, n, x, y, 1, k);
        }
        else
            printf("%lld\n", ask(1, n, x, y, 1));
    }
    return 0;
}