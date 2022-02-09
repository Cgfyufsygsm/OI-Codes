#include <bits/stdc++.h>
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
            fa[find(x)] = find(y + n);
            fa[find(y)] = find(x + n);
        } else if (c[0] == 'F') {
            fa[find(x)] = find(y);
        }
    }
    std::set<int> S;
    FOR(i, 1, n) S.insert(find(i));
    printf("%d\n", S.size());
    return 0;
}