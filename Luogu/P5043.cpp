#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

using ull = unsigned long long;
const int maxn = 55, N = 2500;
int pri[N + 5], isp[N + 5], totp, m;

void sieve() {
    FOR(i, 2, N) {
        if (!isp[i]) pri[++totp] = i;
        for (int j = 1; j <= totp && i * pri[j] <= N; ++j) {
            isp[i * pri[j]] = 1;
            if (i % pri[j] == 0) break;
        }
    }
    return;
}

struct Tree {
    int n, size[maxn], fa[maxn];
    ull f[maxn], g[maxn];
    vector<int> G[maxn];
    void dfs1(int u, int pre) {
        size[u] = f[u] = 1, fa[u] = pre;
        for (int v : G[u]) if (v != pre) {
            dfs1(v, u);
            size[u] += size[v];
            f[u] += f[v] * pri[size[v]];
        }
        return;
    }
    void dfs2(int u) {
        for (int v : G[u]) if (v != fa[u]) {
            g[v] = pri[n - size[v]] * (g[u] - f[v] * pri[size[v]]) + f[v];
            dfs2(v);
        }
        return;
    }
    void init() {
        cin >> n;
        FOR(i, 1, n) {
            int fa; cin >> fa;
            if (fa) G[fa].emplace_back(i), G[i].emplace_back(fa);
        }
        dfs1(1, 0), g[1] = f[1], dfs2(1);
        return;
    }
} t[maxn];

int main() {
    sieve();
    cin >> m;
    FOR(i, 1, m) t[i].init();
    FOR(T1, 1, m) {
        set<ull> S;
        FOR(i, 1, t[T1].n) S.insert(t[T1].g[i]);
        bool flg = 0;
        FOR(T2, 1, m) if (t[T2].n == t[T1].n) {
            FOR(i, 1, t[T2].n) if (S.count(t[T2].g[i])) {
                flg = 1;
                cout << T2 << endl;
                break;
            }
            if (flg) break;
        }
    }
    return 0;
}