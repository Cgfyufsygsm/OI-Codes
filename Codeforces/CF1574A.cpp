#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

int main() {
    int T, n;
    scanf("%d", &T);
    while (T--) {
        scanf("%d", &n);
        FOR(k, 1, n) {
            FOR(i, 1, k) putchar('(');
            FOR(i, 1, k) putchar(')');
            FOR(i, 1, n - k) printf("()");
            puts("");
        }
    }
    return 0;
}