#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 405;
char str[maxn];
int sum[maxn][maxn], a[maxn][maxn];
int f[2][maxn][maxn];

template<typename T> inline T min(const T &a, const T &b) {return a < b ? a : b;}

int cnt1(int y, int i, int j) {return sum[j][y] - sum[i - 1][y];}
int cnt0(int y, int i, int j) {return j - i + 1 - cnt1(y, i, j);}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n, m;
        scanf("%d %d", &n, &m);
        FOR(i, 1, n) {
            scanf("%s", str + 1);
            FOR(j, 1, m) a[i][j] = str[j] - '0';
        }
        FOR(j, 1, m) FOR(i, 1, n) sum[i][j] = sum[i - 1][j] + a[i][j];
        FOR(i, 1, n) FOR(j, i + 4, n) f[1][i][j] = 1e9;
        int ans = 1e9;
        FOR(l, 4, m) {
            FOR(i, 1, n - 4) {
                FOR(j, i + 4, n) {
                    f[l & 1][i][j] = f[(l & 1) ^ 1][i][j] - cnt0(l - 1, i + 1, j - 1) + cnt1(l - 1, i + 1, j - 1)
                        + cnt0(l, i + 1, j - 1) + (1 - a[i][l - 1]) + (1 - a[j][l - 1]);
                    f[l & 1][i][j] = min(f[l & 1][i][j], cnt0(l - 3, i + 1, j - 1) + cnt1(l - 2, i + 1, j - 1) + cnt1(l - 1, i + 1, j - 1)
                        + cnt0(l, i + 1, j - 1) + (2 - a[i][l - 1] - a[i][l - 2]) + (2 - a[j][l - 1] - a[j][l - 2]));
                    ans = min(ans, f[l & 1][i][j]);
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}