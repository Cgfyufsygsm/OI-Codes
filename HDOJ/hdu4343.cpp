#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5, maxs = 18;

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

inline int min(int a, int b) {return a < b ? a : b;}

struct node
{
    int l, r;
    bool operator<(const node &b) const {return l == b.l ? r < b.r : l < b.l;}
} a[maxn];

int nxt[maxn << 1][maxs], n, m, p[maxn << 1], tot;

int ask(int l, int r)
{
    if (l > r || l >= tot) return 0;
    int sum = 0;
    DEC(i, maxs - 1, 0)
        if (nxt[l][i] <= r)
            sum += (1 << i), l = nxt[l][i];
    return sum;
}

int main()
{
    while (scanf("%d %d", &n, &m) == 2)
    {
        FOR(i, 1, n)
        {
            a[i].l = read(), a[i].r = read();
            p[i] = a[i].l, p[i + n] = a[i].r;
        }
        std::sort(p + 1, p + 2 * n + 1);
        tot = std::unique(p + 1, p + 2 * n + 1) - p;
        FOR(i, 1, n)
            a[i].l = std::lower_bound(p + 1, p + tot, a[i].l) - p, a[i].r = std::lower_bound(p + 1, p + tot, a[i].r) - p;
        std::sort(a + 1, a + n + 1);
        for (int i = tot - 1, now = n, r = tot; i; --i)
        {
            while (now && a[now].l >= i) r = min(r, a[now--].r);
            nxt[i][0] = r;
        }
        FOR(j, 1, maxs - 1)
            FOR(i, 1, tot - 1)
                if (nxt[i][j - 1] < tot)
                    nxt[i][j] = nxt[nxt[i][j - 1]][j - 1];
                else nxt[i][j] = tot;
        FOR(i, 1, m)
        {
            int l = read(), r = read();
            l = std::lower_bound(p + 1, p + tot, l) - p;
            r = std::upper_bound(p + 1, p + tot, r) - p - 1;
            printf("%d\n", ask(l, r));
        }
    }
    return 0;
}