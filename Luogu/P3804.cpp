#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define il inline

const int maxn = 1e6 + 5;

char s[maxn];
int len;

struct node {
    int ch[26], len, fa, size;
    node() {memset(ch, 0, sizeof ch), len = fa = size = 0;}
} sam[maxn << 1];

il int max(int a, int b) {return a > b ? a : b;}

int las = 1, tot = 1, ans;
int head[maxn << 1], to[maxn << 2], nxt[maxn << 2], cnte;

void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void add(int c) {
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1)
            sam[cur].fa = q;
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

void dfs(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        dfs(v);
        sam[u].size += sam[v].size;
    }
    if (sam[u].size != 1)
        ans = max(ans, sam[u].len * sam[u].size);
    return;
}

int main() {
    scanf("%s", s + 1), len = strlen(s + 1);
    FOR(i, 1, len) add(s[i] - 'a');
    int p = 1;
    FOR(i, 1, len) p = sam[p].ch[s[i] - 'a'], sam[p].size = 1;
    FOR(i, 2, tot) add(sam[i].fa, i);
    dfs(1);
    printf("%d\n", ans);
    return 0;
}