#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

typedef long long ll;
inline int min(int a, int b) {return a < b ? a : b;}

const int maxn = 2e5 + 5, mod = 1e9 + 7;
int a[maxn], n, q;
int p[maxn], isp[maxn], tot, minfact[maxn];

ll qpow(ll base, ll p = mod - 2)
{
    ll ret = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ret = ret * base % mod;
        base = base * base % mod;
    }
    return ret;
}

void make_prime()
{
    FOR(i, 2, maxn - 2)
    {
        if (!isp[i])
            p[++tot] = i, minfact[i] = tot;
        for (int j = 1; i * p[j] < maxn; ++j)
        {
            isp[i * p[j]] = 1;
            minfact[i * p[j]] = j;
            if (i % p[j] == 0) break;
        }
    }
    return;
}

const int maxp = 2e7 + 5;
int cnt, lson[maxp], rson[maxp], val[maxp];
int root[maxn];

void modify(int &now, int l, int r, int x, int add)
{
    if (!now)
        now = ++cnt;
    if (l == r)
    {
        val[now] += add;
        return;
    }
    int mid = (l + r) >> 1;
    if (x <= mid)
        modify(lson[now], l, mid, x, add);
    else modify(rson[now], mid + 1, r, x, add);
    val[now] = min(val[lson[now]], val[rson[now]]);
    return;
}

int main()
{
    make_prime();
    n = read(), q = read();
    ll gcd = 1;
    FOR(i, 1, n)
    {
        int tmp = read();
        for (int j = minfact[tmp]; tmp > 1;)
        {
            int k = 0;
            while (tmp > 1 && tmp % p[j] == 0)
                ++k, tmp /= p[j];
            gcd = gcd * qpow(qpow(p[j], val[root[j]])) % mod;
            modify(root[j], 1, n, i, k);
            gcd = gcd * qpow(p[j], val[root[j]]) % mod;
            if (tmp > 1) j = minfact[tmp];
        }
    }
    while (q--)
    {
        int x = read(), v = read();
        for (int j = minfact[v]; v > 1;)
        {
            while (v > 1 && v % p[j]) ++j;
            int k = 0;
            while (v > 1 && v % p[j] == 0)
                ++k, v /= p[j];
            gcd = gcd * qpow(qpow(p[j], val[root[j]])) % mod;
            modify(root[j], 1, n, x, k);
            gcd = gcd * qpow(p[j], val[root[j]]) % mod;
            if (v > 1) j = minfact[v];
        }
        printf("%lld\n", gcd);
    }
    return 0;
}