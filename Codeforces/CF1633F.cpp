#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 2e5 + 5;
int n, fa[maxn], size[maxn], son[maxn], dep[maxn], top[maxn];
int dfn[maxn], dfnTot, nfd[maxn], a[maxn];
vector<pair<int, int>> G[maxn];

void dfs1(int u, int pre) {
    fa[u] = pre, dep[u] = dep[pre] + 1, size[u] = 1;
    for (const auto &e : G[u]) if (e.first != pre) {
        const int &v = e.first;
        a[v] = e.second;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son[u]]) son[u] = v;
    }
    return;
}

void dfs2(int u, int topf) {
    top[u] = topf, nfd[dfn[u] = ++dfnTot] = u;
    if (son[u]) dfs2(son[u], topf);
    for (const auto &e : G[u]) if (e.first != son[u] && e.first != fa[u]) {
        const int &v = e.first;
        dfs2(v, v);
    }
    return;
}

struct SGT {
    ll sum[maxn << 2], s[maxn << 2];
    int cnt[maxn << 2], tag[maxn << 2];
    #define L (k << 1)
    #define R (L | 1)
    #define M ((i + j) >> 1)
    il void pushUp(int k) {
        s[k] = s[L] + s[R];
        cnt[k] = cnt[L] + cnt[R];
        return;
    }
    il void pushTag(int i, int j, int k) {
        tag[k] ^= 1;
        cnt[k] = j - i + 1 - cnt[k];
        s[k] = sum[k] - s[k];
        return;
    }
    il void pushDown(int i, int j, int k) {
        if (!tag[k]) return;
        pushTag(i, M, L), pushTag(M + 1, j, R);
        tag[k] = 0;
    }
    void build(int i, int j, int k) {
        if (i == j) {
            sum[k] = a[nfd[i]];
            cnt[k] = (i == 1);
            return;
        }
        build(i, M, L), build(M + 1, j, R);
        sum[k] = sum[L] + sum[R];
        return pushUp(k);
    }
    void modify(int i, int j, int k, int x, int y) {
        if (x <= i && y >= j) return pushTag(i, j, k);
        pushDown(i, j, k);
        if (x <= M) modify(i, M, L, x, y);
        if (y > M) modify(M + 1, j, R, x, y);
        return pushUp(k);
    }
} tree;

int act[maxn], used[maxn], totAct = 1;
vector<int> match;

void getAns(int u) {
    for (const auto &e : G[u]) {
        const int &v = e.first;
        if (v == fa[u] || !act[v]) continue;
        getAns(v);
        if (!used[v]) used[u] = 1, match.push_back(e.second);
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n - 1) {
        int u, v; cin >> u >> v;
        G[u].emplace_back(v, i), G[v].emplace_back(u, i);
    }
    dfs1(1, 0), dfs2(1, 1);
    tree.build(1, n, 1);
    int op;
    ll ans = 0;
    while (cin >> op) {
        if (op == 1) {
            int u; cin >> u;
            act[u] = 1, ++totAct;
            while (u) {
                tree.modify(1, n, 1, dfn[top[u]], dfn[u]);
                u = fa[top[u]];
            }
            if (tree.cnt[1] * 2 == totAct) ans = tree.s[1];
            else ans = 0;
            cout << ans << endl;
        } else if (op == 2) {
            if (ans) {
                vector<int>().swap(match);
                memset(used, 0, sizeof used);
                getAns(1);
                sort(match.begin(), match.end());
                cout << match.size() << ' ';
                for (const int &x : match) cout << x << ' ';
                cout << endl;
            } else cout << 0 << endl;
        } else break;
    }
    return 0;
}