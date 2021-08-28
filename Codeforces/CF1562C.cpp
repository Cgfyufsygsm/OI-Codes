#include <cstdio>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 2e4 + 5;
char s[maxn];
int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        scanf("%s", s + 1);
        bool flag = 1;
        int pos;
        FOR(i, 1, n) if (s[i] == '0') {flag = 0, pos = i; break;}
        if (flag) {
            printf("%d %d %d %d\n", 1, n - 1, 2, n);
        } else if (pos <= n / 2) {
            printf("%d %d %d %d\n", pos, n, pos + 1, n);
        } else {
            printf("%d %d %d %d\n", 1, pos, 1, pos - 1);
        }
    }
    return 0;
}