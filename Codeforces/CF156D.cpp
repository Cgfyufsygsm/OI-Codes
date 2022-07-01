#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5;
int n, m, mod;
int sz[maxn], fa[maxn];

int find(int x) {return x == fa[x] ? x : fa[x] = find(fa[x]);}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m >> mod;
    FOR(i, 1, n) fa[i] = i, sz[i] = 1;
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        u = find(u), v = find(v);
        if (u != v) fa[u] = v, sz[v] += sz[u];
    }
    int ans = 1, cnt = 0;
    FOR(i, 1, n) if (find(i) == i) ans = 1ll * ans * sz[i] % mod, ++cnt;
    if (cnt == 1) ans = 1 % mod;
    else FOR(i, 1, cnt - 2) ans = 1ll * n * ans % mod;
    cout << ans << endl;
    return 0;
}