#include <cstdio>
#include <cmath>
#include <algorithm>
#define FOR(i, a, b) for (signed i = a; i <= b; ++i)
#define DEC(i, a, b) for (signed i = a; i >= b; --i)

typedef double db;
const db EPS = 1e-8;

int n;
db pos[12][12];
db a[12][12], ans[12];

int main()
{
    scanf("%d", &n);
    FOR(i, 1, n + 1)
        FOR(j, 1, n)
            scanf("%lf", &pos[i][j]);
    FOR(i, 1, n)
        FOR(j, 1, n)
        {
            a[i][j] = 2 * (pos[i][j] - pos[i + 1][j]);
            a[i][n + 1] += pos[i][j] * pos[i][j] - pos[i + 1][j] * pos[i + 1][j];
        }
    FOR(i, 1, n)
    {
        int r = i;
        FOR(j, i + 1, n)
            if (fabs(a[r][i]) < fabs(a[j][i]))
                r = j;
        std::swap(a[i], a[r]);
        db div = a[i][i];
        FOR(j, i, n + 1)
            a[i][j] /= div;
        FOR(j, i + 1, n)
        {
            db div = a[j][i];
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
        printf("%.3lf ", ans[i]);
    return 0;
}