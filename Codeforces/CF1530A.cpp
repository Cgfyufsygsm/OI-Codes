#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

il int max(int a, int b) {return a > b ? a : b;}

int main() {
    int t;
    scanf("%d", &t);
    while (t--) {
        char s[12];
        scanf("%s", s + 1);
        int ans = 0;
        for (int i = 1; s[i]; ++i)
            ans = max(ans, s[i] - '0');
        printf("%d\n", ans);
    }
    return 0;
}