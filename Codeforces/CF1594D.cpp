#include <iostream>
#include <vector>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 2e5 + 5;
using namespace std;

int n, m, fa[maxn << 1], size[maxn << 1], col[maxn << 1], cnt[2], vis[maxn << 1];
vector<int> G[maxn << 1];

il int find(int u) {return u == fa[u] ? u : fa[u] = find(fa[u]);}

il void uni(int u, int v) {
    u = find(u), v = find(v);
    if (u != v) fa[u] = v;
    return;
}

void dfs(int u, int c) {
    col[u] = c;
    cnt[c] += size[u];
    vis[u] = 1;
    for (auto v : G[u]) if(!vis[v]) dfs(v, c ^ 1);
    return;
}

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        FOR(i, 1, n << 1) fa[i] = i, size[i] = 0, G[i].clear(), col[i] = -1, vis[i] = 0;
        bool flag = 0;
        while (m--) {
            int u, v;
            char str[15];
            cin >> u >> v >> str;
            if (str[0] == 'c') uni(u, v), uni(u + n, v + n);
            else if (str[0] == 'i') uni(u, v + n), uni(v, u + n);
        }
        FOR(i, 1, n) {
            if (find(i) == find(i + n)) {
                flag = 1;
                break;
            }
            ++size[find(i)];
            G[find(i)].push_back(find(i + n));
            G[find(i + n)].push_back(find(i));
        }
        if (flag) {
            cout << -1 << endl;
            continue;
        }
        int ans = 0;
        FOR(i, 1, n << 1) {
            if (vis[i] || find(i) != i) continue;
            cnt[0] = cnt[1] = 0;
            dfs(i, 0);
            ans += max(cnt[0], cnt[1]);
        }
        cout << ans << endl;
    }
    return 0;
}