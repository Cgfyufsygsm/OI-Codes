#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define int long long

const int maxn = 2e5 + 5;

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

struct node
{
    int val, id;
    bool operator<(const node &b)const
    {
        return val == b.val ? id < b.id : val < b.val;
    }
} ai[maxn], bi[maxn];

int a[maxn], b[maxn], n;

inline int myabs(int x)
{
    return x >= 0 ? x : -x;
}

int f[maxn << 2], tag[maxn << 1], d[maxn];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void build(int i, int j, int k)
{
    if (i == j)
        return void(f[k] = i);
    build(i, M, L);
    build(M + 1, j, R);
    f[k] = f[L] + f[R];
    return;
}

void pushdown(int i, int j, int k)
{
    tag[L] += tag[k], tag[R] += tag[k];
    f[L] += (M - i + 1) * tag[k];
    f[R] += (j - M) * tag[k];
    tag[k] = 0;
    return;
}

void modify(int i, int j, int k, int x, int y, int d)
{
    if (x > y) return;
    if (i >= x && j <= y)
    {
        f[k] += d * (j - i + 1);
        tag[k] += d;
        return;
    }
    pushdown(i, j, k);
    if (x <= M) modify(i, M, L, x, y, d);
    if (y > M) modify(M + 1, j, R, x, y, d);
    f[k] = f[L] + f[R];
    return;
}

int query(int i, int j, int k, int x)
{
    if (i == j) return f[k];
    pushdown(i, j, k);
    if (x <= M) return query(i, M, L, x);
    else return query(M + 1, j, R, x);
}

signed main()
{
    n = read();
    FOR(i, 1, n) a[i] = read(), ai[i].val = a[i] + i, ai[i].id = i;
    FOR(i, 1, n) b[i] = read(), bi[i].val = b[i] + i, bi[i].id = i;
    std::sort(ai + 1, ai + n + 1);
    std::sort(bi + 1, bi + n + 1);
    FOR(i, 1, n)
        if (ai[i].val != bi[i].val) return printf("-1\n"), 0;
        else d[bi[i].id] = ai[i].id;
    build(1, n, 1);
    int ans = 0;
    FOR(i, 1, n)
    {
        ans += abs(query(1, n, 1, d[i]) - i);
        modify(1, n, 1, 1, d[i], 1);
    }
    printf("%lld\n", ans);
    return 0;
}