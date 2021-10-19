#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1e5 + 5;
int n, m;
char s1[maxn], s2[maxn];

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        scanf("%s", s1 + 1);
        scanf("%s", s2 + 1);
        n = strlen(s1 + 1), m = strlen(s2 + 1);
        while (n >= 1) {
            if (s1[n] != s2[m]) n -= 2;
            else --n, --m;
        }
        puts(m ? "NO" : "YES");
    }
    return 0;
}