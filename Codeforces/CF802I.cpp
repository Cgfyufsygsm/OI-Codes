#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

typedef long long ll;

const int maxn = 100000 + 5;

struct node {
    int ch[26], size, fa, len;
} sam[maxn << 1];

char s[maxn];
ll ans = 0;
int las = 1, tot = 1;

void add(int c) {
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

int head[maxn << 1], to[maxn << 1], nxt[maxn << 1], cnte;

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        dfs(v);
        sam[u].size += sam[v].size;
    }
    ans += 1ll * sam[u].size * sam[u].size * (sam[u].len - sam[sam[u].fa].len);
    return;
}

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        memset(sam, 0, sizeof sam);
        memset(head, 0, sizeof head);
        ans = cnte = 0, tot = las = 1;
        scanf("%s", s + 1);
        int n = strlen(s + 1);
        FOR(i, 1, n) add(s[i] - 'a');
        int p = 1;
        FOR(i, 1, n) p = sam[p].ch[s[i] - 'a'], sam[p].size = 1;
        FOR(i, 2, tot) add(sam[i].fa, i);
        dfs(1);
        printf("%lld\n", ans);
    }
    return 0;
}