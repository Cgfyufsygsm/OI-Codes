#include <cstdio>
#include <cctype>
#include <vector>
#include <set>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 1005;
std::vector<int> G[maxn];
int n, pos[maxn << 1], cnt;

void dfs(int u, int fa) {
    pos[++cnt] = u;
    for (auto v : G[u]) {
        if (v == fa) continue;
        dfs(v, u);
        pos[++cnt] = u;
    }
    return;
}

int query(int l, int r) {
    std::set<int> S;
    FOR(i, l, r) S.insert(pos[i]);
    printf("? %d ", S.size());
    for (auto &x : S) printf("%d ", x);
    puts(""), fflush(stdout);
    int ret;
    scanf("%d", &ret);
    return ret;
}

int main() {
    scanf("%d", &n);
    FOR(i, 1, n - 1) {
        int u, v;
        scanf("%d %d", &u, &v);
        G[u].push_back(v), G[v].push_back(u);
    }
    dfs(1, 0);
    int l = 1, r = cnt, w0 = query(1, cnt);
    while (l + 1 < r) {
        int mid = (l + r) >> 1;
        int w1 = query(l, mid);
        if (w1 == w0) r = mid;
        else l = mid;
    }
    printf("! %d %d\n", pos[l], pos[r]), fflush(stdout);
    return 0;
}