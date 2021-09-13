#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 205;
int n;
char s[maxn], ans[maxn][maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d %s", &n, s + 1);
        memset(ans, 0, sizeof ans);
        FOR(i, 1, n) {
            ans[i][i] = 'X';
            if (s[i] == '1')
                FOR(j, 1, n) if (i != j) ans[i][j] = ans[j][i] = '=';
        }
        bool flag = 1;
        FOR(i, 1, n) {
            if (s[i] == '2') {
                bool tmp = 0;
                FOR(j, 1, n) {
                    if (!ans[i][j]) {
                        tmp = 1;
                        ans[i][j] = '+', ans[j][i] = '-';
                        break;
                    }
                }
                if (!tmp) {
                    flag = 0;
                    break;
                }
            }
        }
        FOR(i, 1, n) {
            FOR(j, 1, n)
                if (!ans[i][j]) ans[i][j] = '+', ans[j][i] = '-';
        }
        if (flag) {
            puts("YES");
            FOR(i, 1, n) {
                FOR(j, 1, n) printf("%c", ans[i][j]);
                puts("");
            }
        } else puts("NO");
    }
    return 0;
}