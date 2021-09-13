#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1e5 + 5;
char s[maxn], t[maxn];
int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d %s %s", &n, s + 1, t + 1);
        int ans = 0;
        FOR(i, 1, n) {
            if (s[i] != t[i]) ans += 2;
            else if (s[i] == t[i] && s[i] == '0') {
                if (i < n && s[i + 1] == t[i + 1] && s[i + 1] == '1') ans += 2, ++i;
                else ans += 1;
            } else if (s[i] == t[i] && s[i] == '1') {
                if (i < n && s[i + 1] == t[i + 1] && s[i + 1] == '0') ans += 2, ++i;
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}