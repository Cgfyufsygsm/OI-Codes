#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e6 + 5;
char s[maxn];

struct Node {
    int ch[26], fa, len, size, vis;
} sam[maxn];

int las = 1, tot = 1;

void add(int c) {
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1;
    int p = las;
    for (; p && !sam[p].ch[c]; p = sam[p].fa) sam[p].ch[c] = cur;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else {
            int clone = ++tot;
            sam[clone] = sam[q];
            sam[clone].len = sam[p].len + 1;
            for (; p && sam[p].ch[c] == q; p = sam[p].fa) sam[p].ch[c] = clone;
            sam[q].fa = sam[cur].fa = clone;
        }
    }
    las = cur;
}

vector<int> G[maxn];

void dfs(int u) {
    for (auto &v : G[u]) {
        dfs(v);
        sam[u].size += sam[v].size;
    }
    return;
}

int main() {
    cin >> (s + 1);
    int n = strlen(s + 1);
    FOR(i, 1, n) add(s[i] - 'a');
    for (int i = 1, p = 1; i <= n; ++i) p = sam[p].ch[s[i] - 'a'], sam[p].size = 1;
    FOR(i, 2, tot) G[sam[i].fa].push_back(i);
    dfs(1);
    int q; cin >> q;
    FOR(kase, 1, q) {
        cin >> (s + 1);
        int n = strlen(s + 1);
        int len = 0, u = 1;
        auto extend = [&](int c) {
            for (; u && !sam[u].ch[c]; u = sam[u].fa) len = sam[sam[u].fa].len;
            if (sam[u].ch[c]) ++len, u = sam[u].ch[c];
            return;
        };
        FOR(i, 1, n) extend(s[i] - 'a');
        long long ans = 0;
        FOR(i, 1, n) {
            if (len == n && sam[u].vis < kase) ans += sam[u].size, sam[u].vis = kase;
            extend(s[i] - 'a');
            if (len > n && --len == sam[sam[u].fa].len) u = sam[u].fa;
        }
        cout << ans << endl;
    }
    return 0;
}