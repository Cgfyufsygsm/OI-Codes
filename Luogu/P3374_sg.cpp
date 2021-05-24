#include <cstdio>
#define L (k << 1)
#define R (L | 1)
#define M (i + j >> 1)
#define f(i, a, b) for (int i = a; i <= b; i++)

const int maxn = 5e5 + 5;

int a[maxn], f[maxn << 2];

inline int read()
{
    int s = 0, w = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9')
    {
        if (ch == '-')
            w = -1;
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9')
        s = s * 10 + ch - '0', ch = getchar();
    return s * w;
}

void build(int i, int j, int k)
{
    if (i == j)
        f[k] = a[i];
    else
    {
        build(i, M, L);
        build(M + 1, j, R);
        f[k] = f[L] + f[R];
    }
    return;
}

void add(int x, int d, int i, int j, int k)
{
    if (i == j)
        f[k] += d;
    else
    {
        if (x <= M)
            add(x, d, i, M, L);
        if (x > M)
            add(x, d, M + 1, j, R);
        f[k] = f[L] + f[R];
    }
    return;
}

int ask(int u, int v, int i, int j, int k)
{
    if (i == u && j == v)
        return f[k];
    if (v <= M)
        return ask(u, v, i, M, L);
    if (u > M)
        return ask(u, v, M + 1, j, R);
    return ask(u, M, i, M, L) + ask(M + 1, v, M + 1, j, R);
}

int main()
{
    int n = read(), m = read();
    f(i, 1, n) a[i] = read();
    build(1, n, 1);
    f(i, 1, m)
    {
        int type = read(), x = read(), y = read();
        if (type == 1)
            add(x, y, 1, n, 1);
        if (type == 2)
            printf("%d\n", ask(x, y, 1, n, 1));
    }
    return 0;
}