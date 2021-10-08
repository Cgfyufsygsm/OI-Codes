#include <cstdio>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 105;
char s[maxn];
int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        scanf("%s", s + 1);
        int ans = 0;
        FOR(i, 1, n) {
            if (s[i] == '0') continue;
            ans += s[i] - '0' + (i != n);
        }
        printf("%d\n", ans);
    }
    return 0;
}