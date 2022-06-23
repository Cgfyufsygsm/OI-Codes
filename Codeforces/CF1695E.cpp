#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 3e5 + 5;
int head[maxn << 1], to[maxn << 2], nxt[maxn << 2], cnte = 1;
int n, vis[maxn << 1], vise[maxn << 2];

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

vector<int> path;

void dfs(int u, int pre) {
    path.push_back(u);
    if (vis[u]) return;
    vis[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) if (!vise[i]) {
        vise[i] = vise[i ^ 1] = 1;
        dfs(to[i], i);
        path.push_back(u);
    }
    return;
}

int ans[2][maxn];
char sol1[2][maxn], sol2[2][maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n) {
        int x, y; cin >> x >> y;
        add(x, y), add(y, x);
    }
    int col = 0;
    FOR(i, 1, n << 1) if (!vis[i]) {
        vector<int>().swap(path);
        dfs(i, 0);
        if (path.size() == 3) return puts("-1"), 0;
        else if (path.size() < 3) continue;
        path.pop_back();
        int k = path.size() >> 1;
        auto it = path.begin();
        FOR(i, 1, k) ans[0][i + col] = *it++;
        DEC(i, k, 1) ans[1][i + col] = *it++;
        for (int i = 2; i <= k; i += 2) sol1[0][col + i] = sol1[1][col + i] = 'R', sol1[0][col + i - 1] = sol1[1][col + i - 1] = 'L';
        for (int i = 3; i <= k; i += 2) sol2[0][col + i] = sol2[1][col + i] = 'R', sol2[0][col + i - 1] = sol2[1][col + i - 1] = 'L';
        if (k & 1) sol1[0][col + k] = 'U', sol1[1][col + k] = 'D';
        else sol2[0][col + k] = 'U', sol2[1][col + k] = 'D';
        sol2[0][col + 1] = 'U', sol2[1][col + 1] = 'D';
        col += k;
    }
    cout << 2 << ' ' << col << '\n';
    FOR(i, 0, 1) {
        FOR(j, 1, col) cout << ans[i][j] << ' ';
        cout << '\n';
    }
    FOR(i, 0, 1) {
        FOR(j, 1, col) cout << sol1[i][j];
        cout << '\n';
    }
    FOR(i, 0, 1) {
        FOR(j, 1, col) cout << sol2[i][j];
        cout << '\n';
    }
    return 0;
}