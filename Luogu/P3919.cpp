#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e6 + 5, maxm = 2e7;

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

int n, m;

struct node
{
    int ls, rs, val;
} t[maxm];

#define L t[k].ls
#define R t[k].rs
#define M ((i + j) >> 1)

int cnt, root[maxn];

int clone(int u)
{
    t[++cnt] = t[u];
    return cnt;
}

void build(int &k, int i, int j)
{
    k = ++cnt;
    if (i == j)
    {
        t[k].val = read();
        return;
    }
    build(L, i, M);
    build(R, M + 1, j);
    return;
}

int modify(int k, int i, int j, int x, int val)
{
    k = clone(k);
    if (i == j)
    {
        t[k].val = val;
        return k;
    }
    if (x <= M) L = modify(L, i, M, x, val);
    else R = modify(R, M + 1, j, x, val);
    return k;
}

int query(int k, int i, int j, int x)
{
    if (i == j) return t[k].val;
    if (x <= M) return query(L, i, M, x);
    else return query(R, M + 1, j, x);
}

int main()
{
    n = read(), m = read();
    build(root[0], 1, n);
    FOR(i, 1, m)
    {
        int rt = read(), op = read(), x = read();
        if (op == 1) root[i] = modify(root[rt], 1, n, x, read());
        else printf("%d\n", query(root[rt], 1, n, x)), root[i] = root[rt];
    }
    return 0;
}