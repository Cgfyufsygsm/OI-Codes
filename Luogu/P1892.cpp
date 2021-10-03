#include <cstdio>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 10005;

int fa[maxn], n, m;

il int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

int main() {
    scanf("%d %d", &n, &m);
    FOR(i, 1, n << 1) fa[i] = i;
    FOR(i, 1, m) {
        char c[3]; int x, y;
        scanf("%s %d %d", c, &x, &y);
        if (c[0] == 'E') {
            fa[find(x + n)] = find(y);
            fa[find(y + n)] = find(x);
        } else if (c[0] == 'F') {
            fa[find(x)] = find(y);
        }
    }
    int ans = 0;
    FOR(i, 1, n) if (fa[i] == i) ++ans;
    printf("%d\n", ans);
    return 0;
}