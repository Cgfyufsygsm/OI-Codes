#include <cstdio>
#include <cctype>
#define il inline
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

int n, m, q;
int a[maxn], L[maxn], R[maxn], op[maxn];

struct node
{
    int sum, tag, len;
} t[maxn << 2];
//tag 1: 升序 ；-1 降序

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

il void pushup(int k)
{
    t[k].sum = t[L].sum + t[R].sum;
    return;
}

il void pushdown(int k)
{
    if (t[k].tag == -1) return;
    t[L].sum = t[L].len * t[k].tag;
    t[R].sum = t[R].len * t[k].tag;
    t[L].tag = t[R].tag = t[k].tag;
    t[k].tag = -1;
    return;
}

void build(int i, int j, int k, int val)
{
    t[k].sum = 0, t[k].tag = -1, t[k].len = j - i + 1;
    if (i == j)
    {
        t[k].sum = (a[i] >= val);
        return;
    }
    build(i, M, L, val);
    build(M + 1, j, R, val);
    pushup(k);
    return;
}

int query(int i, int j, int k, int x, int y)
{
    if (x <= i && y >= j) return t[k].sum;
    pushdown(k);
    int ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret += query(M + 1, j, R, x, y);
    return ret;
}

void modify(int i, int j, int k, int x, int y, int v)
{
    if (x > y) return;
    if (x <= i && y >= j)
    {
        t[k].sum = t[k].len * v;
        t[k].tag = v;
        return;
    }
    pushdown(k);
    if (x <= M) modify(i, M, L, x, y, v);
    if (y > M) modify(M + 1, j, R, x, y, v);
    pushup(k);
    return;
}

#undef L
#undef R
#undef M

bool check(int mid)
{
    build(1, n, 1, mid);
    FOR(i, 1, m)
    {
        int len = query(1, n, 1, L[i], R[i]);
        if (op[i] == 1)
            modify(1, n, 1, L[i], L[i] + len - 1, 1), modify(1, n, 1, L[i] + len, R[i], 0);
        else modify(1, n, 1, L[i], R[i] - len, 0), modify(1, n, 1, R[i] - len + 1, R[i], 1);
    }
    return query(1, n, 1, q, q);
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n) a[i] = read();
    FOR(i, 1, m) op[i] = read(), L[i] = read(), R[i] = read();
    q = read();
    int l = 1, r = n, ans;
    while (l <= r)
    {
        int mid = (l + r) >> 1;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    printf("%d\n", ans);
    return 0;
}