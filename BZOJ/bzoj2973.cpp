#include <cstdio>
#include <cctype>
#include <cstring>
#define R register
#define il inline
#define FOR(i, a, b) for (R signed i = a; i <= b; ++i)
#define int long long
#define dbg printf("debug\n")

char act[11][7], org[11][11];
int actlen[11];

int n, m, acts, t;
int a[81];

il int num(int i, int j)
{
    return (i - 1) * m + j;
}

il int max(int a, int b) {return a > b ? a : b;}

struct Matrix
{
    int r, c, a[81][81];
    void init(int _r, int _c)
    {
        r = _r, c = _c;
    }
    int max_element()
    {
        int ret = -1e9;
        FOR(i, 0, r)
            FOR(j, 0, c)
                ret = max(ret, a[i][j]);
        return ret;
    }
    Matrix()
    {
        memset(a, 0, sizeof a);
    }
} ans, A[61];

Matrix operator*(const Matrix &a, const Matrix &b)
{
    Matrix ret;
    ret.init(a.r, b.c);
    int r = ret.r, c = ret.c, p = a.c;
    FOR(i, 0, r)
        FOR(j, 0, c)
            FOR(k, 0, p)
                ret.a[i][j] += a.a[i][k] * b.a[k][j];
    return ret;
}

signed main()
{
    scanf("%lld %lld %lld %lld", &n, &m, &t, &acts);
    FOR(i, 1, n)
        scanf("%s", &org[i][1]);
    FOR(i, 1, n)
        FOR(j, 1, m)
            a[num(i, j)] = org[i][j] - '0';
    FOR(i, 0, acts - 1)
        scanf("%s", &act[i][1]), actlen[i] = strlen(&act[i][1]), act[i][0] = act[i][actlen[i]];
    int N = n * m;
    ans.init(0, N);
    ans.a[0][0] = 1;
    FOR(k, 0, 60)
        A[k].init(N, N);
    FOR(k, 1, 60)
    {
        A[k].a[0][0] = 1;
        FOR(i, 1, n)
            FOR(j, 1, m)
            {
                int idx = k % actlen[a[num(i, j)]];
                char opt = act[a[num(i, j)]][idx];
                if (isdigit(opt))
                    A[k].a[0][num(i, j)] = opt - '0', A[k].a[num(i, j)][num(i, j)] = 1;
                else
                {
                    if (opt == 'N' && i - 1 > 0)
                        A[k].a[num(i, j)][num(i - 1, j)] = 1;
                    else if (opt == 'E' && j + 1 <= m)
                        A[k].a[num(i, j)][num(i, j + 1)] = 1;
                    else if (opt == 'S' && i + 1 <= n)
                        A[k].a[num(i, j)][num(i + 1, j)] = 1;
                    else if (opt == 'W' && j - 1 > 0)
                        A[k].a[num(i, j)][num(i, j - 1)] = 1;
                }
            }
        if (k == 1)
            A[0] = A[k];
        else A[0] = A[0] * A[k];
    }
    int q = t / 60, r = t % 60;
    for (; q; q >>= 1)
    {
        if (q & 1)
            ans = ans * A[0];
        A[0] = A[0] * A[0];
    }
    FOR(i, 1, r)
        ans = ans * A[i];
    printf("%lld\n", ans.max_element());
    return 0;
}