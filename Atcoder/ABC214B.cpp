#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)


int main() {
    int s, t;
    scanf("%d %d", &s, &t);
    int ans = 0;
    FOR(i, 0, s) {
        FOR(j, 0, s) {
            FOR(k, 0, s) {
                if (i + j + k > s) break;
                if (i * j * k > t) break;
                ++ans;
            }
        }
    }
    printf("%d\n", ans);
    return 0;
}