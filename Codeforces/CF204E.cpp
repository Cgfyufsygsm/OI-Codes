#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e5 + 5;
int n, m, pos[maxn];
char s[maxn];

struct Node {
    int ch[26], fa, len, c;
    vector<int> q;
} sam[maxn];
int tot = 1, las = 1;

void extend(int c) {
    auto split = [&c](int p, int q) {
        int clone = ++tot;
        sam[clone] = sam[q];
        sam[clone].len = sam[p].len + 1;
        while (p && sam[p].ch[c] == q) sam[p].ch[c] = clone, p = sam[p].fa;
        return sam[q].fa = clone;
    };
    if (sam[las].ch[c]) {
        int q = sam[las].ch[c];
        if (sam[q].len == sam[las].len + 1) las = q;
        else las = split(las, q);
        return;
    }
    int cur = ++tot;
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else sam[cur].fa = split(p, q);
    }
    las = cur;
    return;
}

struct SGT {
    int sum[maxn * 22], ch[maxn * 22][2], tot;
    #define ls(u) ch[u][0]
    #define rs(u) ch[u][1]
    #define M ((i + j) >> 1)
    void insert(int &u, int i, int j, int x) {
        if (!u) u = ++tot;
        if (i == j) return sum[u] = 1, void();
        if (x <= M) insert(ls(u), i, M, x);
        else insert(rs(u), M + 1, j, x);
        sum[u] = sum[ls(u)] + sum[rs(u)];
    }
    int merge(int u1, int u2, int i, int j) {
        if (!u1 || !u2) return u1 + u2;
        int u = ++tot;
        if (i == j) {
            sum[u] = sum[u1] | sum[u2];
            return u;
        }
        ls(u) = merge(ls(u1), ls(u2), i, M);
        rs(u) = merge(rs(u1), rs(u2), M + 1, j);
        sum[u] = sum[ls(u)] + sum[rs(u)];
        return u;
    }
    #undef ls
    #undef rs
    #undef M
} sgt;
int root[maxn];

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs1(int u) {
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        dfs1(v);
        root[u] = sgt.merge(root[u], root[v], 1, n);
    }
    return;
}

void dfs2(int u) {
    sam[u].c = sam[sam[u].fa].c;
    if (sgt.sum[root[u]] >= m)
        sam[u].c += sam[u].len - sam[sam[u].fa].len;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        dfs2(v);
    }
    return;
}

int main() {
    scanf("%d %d", &n, &m);
    FOR(i, 1, n) {
        scanf("%s", s + pos[i]);
        int len = strlen(s + pos[i]);
        pos[i + 1] = pos[i] + len;
        las = 1;
        FOR(j, pos[i], pos[i + 1] - 1) {
            extend(s[j] - 'a');
            sam[las].q.emplace_back(i);
            sgt.insert(root[las], 1, n, i);
        }
    }
    FOR(i, 2, tot) add(sam[i].fa, i);
    dfs1(1), dfs2(1);
    FOR(i, 1, n) {
        int u = 1;
        long long ans = 0;
        FOR(j, pos[i], pos[i + 1] - 1) {
            u = sam[u].ch[s[j] - 'a'];
            ans += sam[u].c;
        }
        printf("%lld ", ans);
    }
    return 0;
}