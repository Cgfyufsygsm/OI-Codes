#include <cstdio>
#include <cmath>
#include <algorithm>
#define FOR(i, a, b) for (signed i = a; i <= b; ++i)
#define DEC(i, a, b) for (signed i = a; i >= b; --i)

typedef double db;
const db EPS = 1e-8;

int n;
db a[105][105], ans[105];

int main()
{
    scanf("%d", &n);
    FOR(i, 1, n)
        FOR(j, 1, n + 1)
            scanf("%lf", &a[i][j]);
    FOR(i, 1, n)
    {
        int r = i;
        FOR(j, i + 1, n)
            if (fabs(a[r][i]) < fabs(a[j][i]))
                r = j;
        if (fabs(a[r][i]) < EPS)
            return printf("No Solution\n"), 0;
        std::swap(a[r], a[i]);
        double div = a[i][i];
        FOR(j, i, n + 1)
            a[i][j] /= div;
        FOR(j, i + 1, n)
        {
            div = a[j][i];
            FOR(k, i, n + 1)
                a[j][k] -= a[i][k] * div;
        }
    }
    ans[n] = a[n][n + 1];
    DEC(i, n - 1, 1)
    {
        ans[i] = a[i][n + 1];
        FOR(j, i + 1, n)
            ans[i] -= a[i][j] * ans[j];
    }
    FOR(i, 1, n)
        printf("%.2lf\n", ans[i]);
    return 0;
}