#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define debug(...) fprintf(stderr, __VA_ARGS__)

using namespace std;
const int maxn = 305;
int n, V, m, a[maxn], b[maxn];
vector<int> G[maxn], T[maxn];
int vis[maxn], deg[maxn];
long long suma, sumb;
queue<int> q;

struct Op {
    int x, y, d;
    Op(int _x = 0, int _y = 0, int _d = 0) : x(_x), y(_y), d(_d) {}
};
vector<Op> ans;

void dfs0(int u) {
    vis[u] = 1;
    suma += a[u], sumb += b[u];
    for (auto &v : G[u]) if (!vis[v]) {
        T[u].push_back(v), T[v].push_back(u);
        ++deg[u], ++deg[v];
        dfs0(v);
    }
    if (deg[u] == 1) q.push(u);
    return;
}

int dfs1(int u, int fa, int in) { // 返回消化了的流量
    int ta = a[u] + in, orga = a[u], out = 0;
    if (ta >= 0 && ta <= V) {
        a[u] = ta;
        if (in >= 0) ans.push_back(Op(fa, u, in));
        else ans.push_back(Op(u, fa, -in));
        return in;
    } else if (ta < 0) { // in < 0 fa 吸血 u
        for (auto &v : T[u]) if (v != fa && vis[v] != 2) {
            int cur = dfs1(v, u, ta);
            ta -= cur, out += cur;
            if (ta >= 0) break;
        }
        a[u] = max(0, ta);
        ans.push_back(Op(u, fa, orga - a[u] - out));
        return a[u] - orga + out;
    } else if (ta > V) {
        for (auto &v : T[u]) if (v != fa && vis[v] != 2) {
            int cur = dfs1(v, u, ta - V);
            ta -= cur, out += cur;
            if (ta <= V) break;
        }
        a[u] = min(V, ta);
        ans.push_back(Op(fa, u, a[u] - orga + out));
        return a[u] - orga + out;
    }
    return 0;
}

int main() {
    cin >> n >> V >> m;
    FOR(i, 1, n) cin >> a[i];
    FOR(i, 1, n) cin >> b[i];
    FOR(i, 1, m) {
        int u, v;
        cin >> u >> v;
        G[u].push_back(v), G[v].push_back(u);
    }
    FOR(i, 1, n) if (!vis[i]) {
        suma = sumb = 0;
        dfs0(i);
        if (suma != sumb) return puts("NO"), 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            int v = -1;
            for (auto &vv : T[u]) if (vis[vv] != 2) {
                v = vv;
                break;
            }
            if (v == -1) continue;
            dfs1(v, u, a[u] - b[u]);
            a[u] = b[u];
            vis[u] = 2;
            if (--deg[v] == 1) q.push(v);
        }
    }
    cout << ans.size() << endl;
    for (auto &o : ans) cout << o.x << ' ' << o.y << ' ' << o.d << '\n';
    return 0;
}