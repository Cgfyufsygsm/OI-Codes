#include <cstdio>
#include <cctype>
#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

const int maxn = 1e5 + 5;
int n, m;

inline int max(int a, int b)
{
    return a > b ? a : b;
}

inline void swap(int &a, int &b)
{
    int t = a;
    a = b;
    b = t;
}

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if (c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

struct seg
{
    int len, rev, tag, sum, pre[2], suf[2], ans[2];

    seg()
    {
        tag = -1;
        rev = 0;
        pre[1] = suf[1] = pre[0] = suf[0] = ans[1] = ans[0] = 0;
    }
} f[maxn << 2];

seg operator+(const seg &a, const seg &b)
{
    seg ret;
    ret.rev = 0;
    ret.sum = a.sum + b.sum;
    ret.len = a.len + b.len;
    ret.tag = -1; //-1 is none,1 is 1,0 is 0
    for (int k = 0; k <= 1; k++)
    {
        ret.pre[k] = a.pre[k];
        if (a.sum == a.len * k)
            ret.pre[k] = a.len + b.pre[k];

        ret.suf[k] = b.suf[k];
        if (b.sum == b.len * k)
            ret.suf[k] = b.len + a.suf[k];

        ret.ans[k] = max(a.ans[k], max(b.ans[k], a.suf[k] + b.pre[k]));
    }
    return ret;
}

void build(int i, int j, int k)
{
    if (i == j)
    {
        int tmp = read();
        f[k].tag = -1;
        f[k].len = 1;
        f[k].sum = tmp;
        f[k].ans[tmp] = f[k].pre[tmp] = f[k].suf[tmp] = 1;
        f[k].ans[tmp ^ 1] = f[k].pre[tmp ^ 1] = f[k].suf[tmp ^ 1] = 0;
        return;
    }
    build(i, M, L);
    build(M + 1, j, R);
    f[k] = f[L] + f[R];
    f[k].len = j - i + 1;
    return;
}

void downrev(int i, int j, int k)
{
    for (int kk = L; kk <= R; kk++)
    {
        f[kk].rev ^= 1;
        f[kk].sum = f[kk].len - f[kk].sum;
        swap(f[kk].pre[0], f[kk].pre[1]);
        swap(f[kk].suf[0], f[kk].suf[1]);
        swap(f[kk].ans[0], f[kk].ans[1]);
        if (f[kk].tag != -1)
        {
            f[kk].tag = f[kk].tag ^ 1;
            f[kk].rev = 0;
        }
    }
    f[k].rev ^= 1;
}

void downall(int i, int j, int k)
{
    for (int kk = L; kk <= R; kk++)
    {
        f[kk].sum = f[kk].len * f[k].tag;
        f[kk].rev = 0;
        f[kk].tag = f[k].tag;
        f[kk].pre[f[k].tag] = f[kk].suf[f[k].tag] = f[kk].ans[f[k].tag] = f[kk].len;
        f[kk].pre[f[k].tag ^ 1] = f[kk].suf[f[k].tag ^ 1] = f[kk].ans[f[k].tag ^ 1] = 0;
    }
    f[k].tag = -1;
    f[k].rev = 0;
}

void all(int i, int j, int k, int x, int y, int opt)
{
    if (x <= i && y >= j)
    {
        f[k].sum = f[k].len * opt;
        f[k].rev = 0;
        f[k].tag = opt;
        f[k].pre[opt] = f[k].suf[opt] = f[k].ans[opt] = f[k].len;
        f[k].pre[opt ^ 1] = f[k].suf[opt ^ 1] = f[k].ans[opt ^ 1] = 0;
        return;
    }
    if (f[k].tag != -1)
        downall(i, j, k);
    if (f[k].rev)
        downrev(i, j, k);
    if (x <= M)
        all(i, M, L, x, y, opt);
    if (y > M)
        all(M + 1, j, R, x, y, opt);
    f[k] = f[L] + f[R];
    return;
}

void rev(int i, int j, int k, int x, int y)
{
    if (x <= i && y >= j)
    {
        f[k].rev = !f[k].rev;
        f[k].sum = f[k].len - f[k].sum;
        swap(f[k].pre[0], f[k].pre[1]);
        swap(f[k].suf[0], f[k].suf[1]);
        swap(f[k].ans[0], f[k].ans[1]);
        if (f[k].tag != -1)
        {
            f[k].tag ^= 1;
            f[k].rev = 0;
        }
        return;
    }
    if (f[k].tag != -1)
        downall(i, j, k);
    if (f[k].rev)
        downrev(i, j, k);
    if (x <= M)
        rev(i, M, L, x, y);
    if (y > M)
        rev(M + 1, j, R, x, y);
    f[k] = f[L] + f[R];
    return;
}

seg query(int i, int j, int k, int x, int y)
{
    if (x <= i && y >= j)
        return f[k];
    if (f[k].tag != -1)
        downall(i, j, k);
    if (f[k].rev)
        downrev(i, j, k);
    if (y <= M)
        return query(i, M, L, x, y);
    if (x > M)
        return query(M + 1, j, R, x, y);
    return query(i, M, L, x, y) + query(M + 1, j, R, x, y);
}

int main()
{
    n = read(), m = read();
    build(1, n, 1);
    while (m--)
    {
        int opt = read(), l = read() + 1, r = read() + 1;
        if (opt == 0 || opt == 1)
            all(1, n, 1, l, r, opt);
        else if (opt == 2)
            rev(1, n, 1, l, r);
        else if (opt == 3)
            printf("%d\n", query(1, n, 1, l, r).sum);
        else if (opt == 4)
            printf("%d\n", query(1, n, 1, l, r).ans[1]);
    }
    return 0;
}