#include <cstdio>
#include <cctype>
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

typedef double db;
const int maxn = 1e5 + 5, mod1 = 39989, mod2 = 1e9;

int cnt = 0;

struct segment
{
    db k, b;
} p[maxn];

int t[mod1 << 2];

il db calc(int i, int x) {return p[i].k * x + p[i].b;}
il int max(int a, int b) {return a > b ? a : b;}
template<typename T> il void swap(T &a, T &b)
{
    T t = a;
    a = b, b = t;
    return;
}

void add(int x0, int y0, int x1, int y1)
{
    ++cnt;
    if (x0 == x1)
        p[cnt].k = 0, p[cnt].b = max(y0, y1);
    else
        p[cnt].k = db(y0 - y1) / db(x0 - x1), p[cnt].b = y0 - p[cnt].k * x0;
    return;
}

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void update(int k, int i, int j, int x, int y, int u)// u 为线段编号
{
    if (x > j || y < i) return;
    int v = t[k];
    db resu = calc(u, M), resv = calc(v, M);
    if (x <= i && y >= j)
    {
        if (i == j)
        {
            if (resu > resv) t[k] = u;
            return;
        }
        if (p[u].k > p[v].k)
        {
            if (resu > resv)
            {
                t[k] = u;
                update(L, i, M, x, y, v);
            }
            else update(R, M + 1, j, x, y, u);
        }
        else if (p[u].k < p[v].k)
        {
            if (resu > resv)
            {
                t[k] = u;
                update(R, M + 1, j, x, y, v);
            }
            else update(L, i, M, x, y, u);
        }
        else if (p[u].b > p[v].b) t[k] = u;
        return;
    }
    update(L, i, M, x, y, u);
    update(R, M + 1, j, x, y, u);
    return;
}

il int cmp(int X, int i, int j) {return calc(i, X) > calc(j, X) ? i : j;}

int query(int X, int k, int i, int j)
{
    if (i > j) return 0;
    int ret = cmp(X, 0, t[k]);
    if (i == j) return ret;
    if (X <= M) ret = cmp(X, ret, query(X, L, i, M));
    else ret = cmp(X, ret, query(X, R, M + 1, j));
    return ret;
}

int main()
{
    int n = read(), last = 0;
    FOR(i, 1, n)
    {
        int op = read();
        if (!op)
        {
            int k = (read() + last - 1) % mod1 + 1;
            printf("%d\n", last = query(k, 1, 1, mod1));
        }
        else
        {
            int x0 = (read() + last - 1) % mod1 + 1, y0 = (read() + last - 1) % mod2 + 1;
            int x1 = (read() + last - 1) % mod1 + 1, y1 = (read() + last - 1) % mod2 + 1;
            if (x0 > x1) swap(x0, x1), swap(y0, y1);
            add(x0, y0, x1, y1);
            update(1, 1, mod1, x0, x1, cnt);
        }
    }
    return 0;
}