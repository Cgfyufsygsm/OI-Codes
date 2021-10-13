#include <cstdio>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1e4 + 5;
int n, k, sum[maxn], a[maxn];

int getsum(int i, int j) {
    int ans1, ans2;
    printf("or %d %d\n", i, j), fflush(stdout);
    scanf("%d", &ans1);
    printf("and %d %d\n", i, j), fflush(stdout);
    scanf("%d", &ans2);
    return ans1 + ans2;
}

int main() {
    scanf("%d %d", &n, &k);
    FOR(i, 2, n) sum[i] = getsum(1, i);
    int tmp = getsum(2, 3);
    a[1] = (sum[2] + sum[3] - tmp) >> 1;
    FOR(i, 2, n) a[i] = sum[i] - a[1];
    std::sort(a + 1, a + n + 1);
    printf("finish %d\n", a[k]), fflush(stdout);
    return 0;
}