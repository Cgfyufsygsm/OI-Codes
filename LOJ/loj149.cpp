#include <cstdio>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e5 + 5;
int n, k;
double a[maxn], b[maxn], val[maxn];

bool check(double ans)
{
    FOR(i, 1, n)
        val[i] = a[i] - b[i] * ans;
    std::sort(val + 1, val + n + 1);
    double ret = 0;
    FOR(i, n - k + 1, n)
        ret += val[i];
    return ret >= 0;
}

int main()
{
    scanf("%d %d", &n, &k);
    FOR(i, 1, n)
        scanf("%lf", a + i);
    FOR(i, 1, n)
        scanf("%lf", b + i);
    double l = 0, r = 1e9, mid;
    while (r - l >= 1e-6)
    {
        mid = (l + r) / 2.0;
        if (check(mid))
            l = mid;
        else r = mid;
    }
    printf("%.4lf\n", mid);
    return 0;
}