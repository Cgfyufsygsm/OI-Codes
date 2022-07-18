#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 1e3 + 5;
vector<int> G[maxn];
int n, B, stk[maxn], top;
int bel[maxn], cnt, root[maxn];

void dfs(int u, int fa) {
    int curTop = top;
    for (auto &v : G[u]) if (v != fa) {
        dfs(v, u);
        if (top - curTop >= B) {
            root[++cnt] = u;
            while (top > curTop) bel[stk[top--]] = cnt;
        }
    }
    stk[++top] = u;
    return;
}

int main() {
    cin >> n >> B;
    FOR(i, 2, n) {
        int u, v; cin >> u >> v;
        G[u].emplace_back(v), G[v].emplace_back(u);
    }
    dfs(1, 0);
    if (!cnt) root[++cnt] = 1;
    while (top) bel[stk[top--]] = cnt;
    cout << cnt << '\n';
    FOR(i, 1, n) cout << bel[i] << " \n"[i == n];
    FOR(i, 1, cnt) cout << root[i] << " \n"[i == n];
    return 0;
}