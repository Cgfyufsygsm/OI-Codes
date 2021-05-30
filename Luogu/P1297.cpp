#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 1e7 + 5;
int a[maxn];

inline int max(int a, int b) {return a > b ? a : b;}

int main()
{
    int A, B, C, n;
    scanf("%d%d%d%d%d", &n, &A, &B, &C, a + 1);
    FOR(i, 2, n)
        a[i] = ((long long) a[i - 1] * A + B) % 100000001;
    FOR(i, 1, n)
        a[i] = a[i] % C + 1;
    double ans = 0;
    a[n + 1] = a[1];
    FOR(i, 1, n) ans += 1.00/double(max(a[i], a[i + 1]));
    printf("%.3lf\n", ans);
    return 0;
}