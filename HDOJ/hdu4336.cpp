#include <cstdio>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using db = double;
int n;
db p[22], ans;

void dfs(int u, db now, int op) {
    if (u == n) {
        if (now > 1e-9) ans += op / now;
        return;
    }
    dfs(u + 1, now + p[u + 1], -op);
    dfs(u + 1, now, op);
    return;
}

int main() {
    while (~scanf("%d", &n)) {
        FOR(i, 1, n) scanf("%lf", p + i);
        ans = 0;
        dfs(0, 0, -1);
        printf("%lf\n", ans);
    }
    return 0;
}