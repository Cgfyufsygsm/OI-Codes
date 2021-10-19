#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 105;

int n, deg[maxn], val[maxn], nxt[maxn];

int main() {
    scanf("%d", &n);
    FOR(j, 1, n) {
        printf("? ");
        FOR(i, 1, n) printf("%d ", i == j ? 2 : 1);
        puts("");
        fflush(stdout);
        int x; scanf("%d", &x);
        if (x && x < j) nxt[j] = x, ++deg[x];
    }
    FOR(j, 1, n) {
        printf("? ");
        FOR(i, 1, n) printf("%d ", i == j ? 1 : 2);
        puts("");
        fflush(stdout);
        int x; scanf("%d", &x);
        if (x && x < j) nxt[x] = j, ++deg[j];
    }

    FOR(i, 1, n) {
        FOR(j, 1, n) {
            if (!deg[j]) {
                val[j] = i, deg[j] = 1;
                --deg[nxt[j]];
                break;
            }
        }
    }

    printf("! ");
    FOR(i, 1, n) printf("%d ", val[i]);
    puts("");
    fflush(stdout);
    return 0;
}