#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

char a[25];

il int max(int a, int b) {return a > b ? a : b;}
il int min(int a, int b) {return a < b ? a : b;}

int solve() {
    static int f[20][25][25];
    memset(f, 0, sizeof f);
    f[1][a[1] - '0'][0] = 1;
    int n = strlen(a + 1);
    FOR(i, 1, n - 1) {
        FOR(j, 1, 20) {
            FOR(k, 0, 20) {
                if (f[i][j][k]) {
                    FOR(l, max((j + 2) / 3, k), min(j, a[i + 1] - '0'))
                        f[i + 1][a[i + 1] - '0'][l] = 1;
                    FOR(l, max((j + 1) / 3, k), min(j - 1, a[i + 1] - '0' + 10))
                        f[i + 1][a[i + 1] - '0' + 10][l] = 1;
                }
            }
        }
    }
    int ans = 1e9;
    FOR(i, 1, 20)
        FOR(j, 0, 20)
            if (f[n][i][j])
                ans = min(ans, max((i + 2) / 3, j));
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    while (T--) {
        scanf("%s", a + 1);
        printf("%d\n", solve());
    }
    return 0;
}