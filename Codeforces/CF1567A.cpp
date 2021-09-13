#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 105;
char s1[maxn], s2[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n; scanf("%d", &n);
        memset(s2, 0, sizeof s2);
        scanf("%s", s1 + 1);
        FOR(i, 1, n)
            if (s1[i] == 'U') s2[i] = 'D';
            else if (s1[i] == 'D') s2[i] = 'U';
        FOR(i, 1, n) if (s2[i] != 'D' && s2[i] != 'U') {
            if (s2[i - 1] != 'L') s2[i] = 'L';
            else s2[i] = 'R';
        }
        FOR(i, 1, n) putchar(s2[i]); puts("");
    }
    return 0;
}