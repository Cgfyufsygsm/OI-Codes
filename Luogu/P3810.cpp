#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define lowbit(x) (x & -x)

const int maxn = 1e5 + 5, maxk = 2e5 + 5;

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
    int a, b, c, cnt, ans;
    bool operator!=(const node &y) const
    {
        return a != y.a || b != y.b || c != y.c;
    }
} s1[maxn], s2[maxn];

inline bool cmp1(node x, node y)
{
    return x.a == y.a ? (x.b == y.b ? x.c < y.c : x.b < y.b) : x.a < y.a;
}

inline bool cmp2(node x, node y)
{
    return x.b == y.b ? x.c < y.c : x.b < y.b;
}

int n, k, m, ans[maxk];

int f[maxk];

void add(int x, int val)
{
    for (; x <= k; x += lowbit(x))
        f[x] += val;
    return;
}

int query(int x)
{
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += f[x];
    return ret;
}

void cdq(int l, int r)
{
    if (l == r) return;
    int mid = (l + r) >> 1;
    cdq(l, mid);
    cdq(mid + 1, r);
    std::sort(s2 + l, s2 + mid + 1, cmp2);
    std::sort(s2 + mid + 1, s2 + r + 1, cmp2);
    int i, j = l;
    for (i = mid + 1; i <= r; ++i)
    {
        while (s2[i].b >= s2[j].b && j <= mid)
        {
            add(s2[j].c, s2[j].cnt);
            ++j;
        }
        s2[i].ans += query(s2[i].c);
    }
    for (i = l; i < j; ++i)
        add(s2[i].c, -s2[i].cnt);
    return;
}

int main()
{
    n = read(), k = read();
    FOR(i, 1, n)
        s1[i].a = read(), s1[i].b = read(), s1[i].c = read();
    std::sort(s1 + 1, s1 + n + 1, cmp1);
    int same = 0;
    FOR(i, 1, n)
    {
        ++same;
        if (s1[i] != s1[i + 1])
        {
            ++m;
            s2[m] = s1[i];
            s2[m].cnt = same;
            s2[m].ans = 0;
            same = 0;
        }
    }
    cdq(1, m);
    FOR(i, 1, m)
        ans[s2[i].ans + s2[i].cnt - 1] += s2[i].cnt;
    FOR(i, 0, n - 1)
        printf("%d\n", ans[i]);
    return 0;
}