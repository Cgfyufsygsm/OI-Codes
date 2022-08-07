#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = __int128;
const int maxn = 1005, mod = 998244353;
int ind[maxn], n, m;
ll a[maxn], aa[maxn];
int ans;
vector<int> G[maxn];

void toposort() {
    set<int> q;
    FOR(i, 1, n) if (!ind[i]) q.insert(i);
    while (!q.empty()) {
        int u = -1;
        for (int x : q) if (u == -1 || a[x] < a[u]) u = x;
        q.erase(u);
        ll tmp = a[u];
        ans = (ans + tmp) % mod;
        FOR(i, 1, n) a[i] += (ind[i] - 1ll) * tmp;
        for (int v : G[u]) if (!--ind[v]) q.insert(v);
    }
}

void solve() {
    cin >> n >> m;
    bool flg = 1;
    FOR(i, 1, n) {
        int x;
        cin >> x; 
        a[i] = x;
        flg &= (!a[i]);
        vector<int>().swap(G[i]);
        ind[i] = 0;
    }
    FOR(i, 1, m) {
        int u, v; cin >> u >> v;
        ++ind[v], G[u].emplace_back(v);
    }
    if (flg) return cout << "0\n", void();
    FOR(i, 1, n) {
        if (i == 1) memcpy(aa, a, sizeof(a[i]) * (n + 1));
        flg = 1;
        FOR(u, 1, n) {
            if (a[u]) {
                flg = 0;
                for (int v : G[u]) ++aa[v];
                --aa[u];
            }
        }
        if (flg) return cout << i - 1 << '\n', void();
        memcpy(a, aa, sizeof(a[i]) * (n + 1));
    }
    ans = n;
    toposort();
    cout << ans << '\n';
    return;
}

int main() {
    ios::sync_with_stdio(false);
    int T; cin >> T;
    while (T--) solve();
    return 0;
}