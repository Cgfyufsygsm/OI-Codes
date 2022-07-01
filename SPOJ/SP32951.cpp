#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using ll = long long;
const int maxn = 3e5 + 5;

struct Node {
    int ch[26], len, fa;
    Node() {memset(ch, 0, sizeof ch), len = fa = 0;}
} sam[maxn << 1];

int las = 1, tot = 1;

void extend(int c) {
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else {
            int clone = ++tot;
            sam[clone] = sam[q];
            sam[clone].len = sam[p].len + 1;
            while (p && sam[p].ch[c] == q) sam[p].ch[c] = clone, p = sam[p].fa;
            sam[q].fa = sam[cur].fa = clone;
        }
    }
    las = cur;
    return;
}

ll ans[maxn << 1];

void dfs(int u) {
    if (ans[u]) return;
    ans[u] = 1;
    FOR(c, 0, 25) if (sam[u].ch[c]) {
        dfs(sam[u].ch[c]);
        ans[u] += ans[sam[u].ch[c]];
    }
    return;
}

char s[maxn << 1];

int main() {
    scanf("%s", s + 1);
    int n = strlen(s + 1);
    FOR(i, 1, n) extend(s[i] - 'a');
    dfs(1);
    FOR(c, 0, 25) printf("%lld ", ans[sam[1].ch[c]]);
    return 0;
}