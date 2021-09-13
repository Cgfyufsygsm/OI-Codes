#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n;
        char s[50];
        scanf("%d %s", &n, s + 1);
        bool flag = 0;
        int l, r;
        FOR(i, 2, n) if (s[i] != s[i - 1]) {
            l = i - 1, r = i, flag = 1;
            break;
        }
        if (flag) printf("%d %d\n", l, r);
        else printf("-1 -1\n");
    }
    return 0;
}