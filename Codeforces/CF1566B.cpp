#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1e5 + 5;
char s[maxn];
int n;

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s + 1);
        n = strlen(s + 1);
        int zero = 0, one = 0;
        FOR(i, 1, n) {
            if (s[i] == '1' && s[i] != s[i - 1]) ++one;
            if (s[i] == '0' && s[i] != s[i - 1]) ++zero;
        }
        if (zero > 1) puts("2");
        else if (!zero && one) puts("0");
        else puts("1");
    }
    return 0;
}