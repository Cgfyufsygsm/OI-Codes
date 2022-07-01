#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using ll = long long;
const int maxn = 1e6 + 5, mod = 1e9 + 7;

struct Node {
    int ch[26], fa, len;
    Node() {memset(ch, 0, sizeof ch), fa = len = 0;}
} sam[maxn << 1];
int rt[maxn], n, tot = 0, las;
char s[maxn];

void extend(int c, int id) {
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = rt[id];
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

int ans[maxn << 1];

il void add(int &a, int b) {a += b; a >= mod ? a -= mod : true;}

void dfs(int u) {
    if (ans[u]) return;
    ans[u] = 1;
    FOR(c, 0, 25) if (sam[u].ch[c]) {
        dfs(sam[u].ch[c]);
        // ans[u] = (ans[u] + ans[sam[u].ch[c]]) % mod;
        add(ans[u], ans[sam[u].ch[c]]);
    }
    return;
}

int main() {
    scanf("%d", &n);
    FOR(i, 1, n) {
        rt[i] = las = ++tot;
        scanf("%s", s + 1);
        int len = strlen(s + 1);
        FOR(j, 1, len) extend(s[j] - 'a', i);
    }
    DEC(i, n - 1, 1)
        FOR(j, rt[i], rt[i + 1] - 1)
            FOR(c, 0, 25) if (!sam[j].ch[c])
                sam[j].ch[c] = sam[rt[i + 1]].ch[c];
    dfs(1);
    printf("%d\n", ans[1]);
    return 0;
}