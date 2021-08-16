#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 105;
int n;
char s[maxn];

il int max(int a, int b) {return a > b ? a : b;}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        scanf("%s", s + 1);
        int pos = 0;
        for (pos = 1; pos <= n; ++pos)
            if (s[pos] != '?') break;
        FOR(i, pos, n)
            if (s[i] != '?') continue;
            else if (s[i - 1] == 'R') s[i] = 'B';
            else if (s[i - 1] == 'B') s[i] = 'R';
        if (pos == n + 1) {
            FOR(i, 1, n) s[i] = (i & 1) ? 'R' : 'B';
        } else {
            DEC(i, pos - 1, 1)
                if (s[i + 1] == 'B') s[i] = 'R';
                else if (s[i + 1] == 'R') s[i] = 'B';
        }
        printf("%s\n", s + 1);
    }
    return 0;
}