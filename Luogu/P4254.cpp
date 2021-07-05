#include <cstdio>
#include <cstring>
#include <cmath>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

typedef double db;

const int maxn = 1e5 + 5, maxt = 5e4 + 5;

struct segment
{
    db k, b;
} p[maxn];

int cnt = 0, t[maxt << 2];

void add(db s, db k)
{
    ++cnt;
    p[cnt].k = k;
    p[cnt].b = s - k;
    return;
}

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

il db calc(int i, int x) {return p[i].k * x + p[i].b;}
il db max(db a, db b) {return a > b ? a : b;} 

void update(int k, int i, int j, int u)
{
    int v = t[k];
    db resu = calc(u, M), resv = calc(v, M);
    if (i == j)
    {
        if (resu > resv) t[k] = u;
        return;
    }
    if (p[u].k > p[v].k)
    {
        if (resu > resv)
            t[k] = u, update(L, i, M, v);
        else update(R, M + 1, j, u);
    }
    else if (p[u].k < p[v].k)
    {
        if (resu > resv)
            t[k] = u, update(R, M + 1, j, v);
        else update(L, i, M, u);
    }
    else if (resu > resv) t[k] = u;
    return;
}

db query(int X, int k, int i, int j)
{
    db res = 0;
    res = max(res, calc(t[k], X));
    if (i >= j) return res;
    if (X <= M) res = max(res, query(X, L, i, M));
    else res = max(res, query(X, R, M + 1, j));
    return res;
}

int main()
{
    int n;
    scanf("%d", &n);
    char op[10];
    while (n--)
    {
        scanf("%s", op + 1);
        if (op[1] == 'Q')
        {
            int t;
            scanf("%d", &t);
            printf("%d\n", (int)floor(query(t, 1, 1, maxt) / 100));
        }
        else if (op[1] == 'P')
        {
            db s, p;
            scanf("%lf %lf", &s, &p);
            add(s, p);
            update(1, 1, maxt, cnt);
        }
    }
    return 0;
}