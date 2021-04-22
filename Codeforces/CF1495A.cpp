#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

typedef double db;

const int maxn = 1e5 + 5;
db x[maxn], y[maxn];
int n, cntx, cnty;

int main()
{
    int T = read();
    while (T--)
    {
        n = read();
        db ans = 0;
        cntx = cnty = 0;
        FOR(i, 1, n << 1)
        {
            int xx = read(), yy = read();
            if (!xx) y[++cnty] = yy;
            if (!yy) x[++cntx] = xx;
        }
        std::sort(x + 1, x + cntx + 1);
        std::sort(y + 1, y + cnty + 1);
        FOR(i, 1, n)
            ans += sqrt(x[i] * x[i] + y[i] * y[i]);
        printf("%.15lf\n", ans);
    }
    return 0;
}