#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

const int maxn = 2e5 + 5, LG = 18;
int n, m, ch[maxn][26], fa[maxn][LG], len[maxn];
int tot = 1, las = 1;
char s[maxn];

struct SGT {
    int t[maxn * 25], ch[maxn * 25][2], tot;
    #define ls(u) ch[u][0]
    #define rs(u) ch[u][1]
    #define M ((i + j) >> 1)
    void insert(int &u, int i, int j, int x) {
        if (!u) u = ++tot;
        ++t[u];
        if (i == j) return;
        if (x <= M) insert(ls(u), i, M, x);
        else insert(rs(u), M + 1, j, x);
        return;
    }
    int merge(int u1, int u2, int i, int j) {
        if (!u1 || !u2) return u1 + u2;
        int u = ++tot;
        if (i == j) t[u] = t[u1] | t[u2];
        else {
            ls(u) = merge(ls(u1), ls(u2), i, M);
            rs(u) = merge(rs(u1), rs(u2), M + 1, j);
            t[u] = t[ls(u)] + t[rs(u)];
        }
        return u;
    }
    int query(int u, int i, int j, int x, int y) {
        if (!u) return 0;
        if (x <= i && y >= j) return t[u];
        int ret = 0;
        if (x <= M) ret += query(ls(u), i, M, x, y);
        if (y > M) ret += query(rs(u), M + 1, j, x, y);
        return ret;
    }
    #undef ls
    #undef rs
    #undef M
} sgt;
int root[maxn];

void extend(int c, int x) {
    int cur = ++tot;
    len[cur] = len[las] + 1;
    int p = las;
    while (p && !ch[p][c]) ch[p][c] = cur, p = fa[p][0];
    if (!p) fa[cur][0] = 1;
    else {
        int q = ch[p][c];
        if (len[q] == len[p] + 1) fa[cur][0] = q;
        else {
            int clone = ++tot;
            memcpy(ch[clone], ch[q], sizeof ch[clone]);
            len[clone] = len[p] + 1, fa[clone][0] = fa[q][0];
            while (p && ch[p][c] == q) ch[p][c] = clone, p = fa[p][0];
            fa[q][0] = fa[cur][0] = clone;
        }
    }
    sgt.insert(root[cur], 1, n, x);
    las = cur;
    return;
}

int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int st[maxn];

void addEdge(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u) {
    FOR(j, 1, LG - 1) fa[u][j] = fa[fa[u][j - 1]][j - 1];
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        dfs(v);
        root[u] = sgt.merge(root[u], root[v], 1, n);
    }
    return;
}

bool check(int lim, int p, int a, int b) {
    DEC(j, LG - 1, 0) if (fa[p][j] && len[fa[p][j]] >= lim) p = fa[p][j];
    return sgt.query(root[p], 1, n, a + lim - 1, b);
}

int main() {
    scanf("%d %d", &n, &m);
    scanf("%s", s + 1);
    reverse(s + 1, s + n + 1);
    FOR(i, 1, n) extend(s[i] - 'a', i), st[i] = las;
    FOR(i, 2, tot) addEdge(fa[i][0], i);
    dfs(1);
    while (m--) {
        int aa, bb, cc, dd; scanf("%d %d %d %d", &aa, &bb, &cc, &dd);
        int a = n - bb + 1, b = n - aa + 1, c = n - dd + 1, d = n - cc + 1;
        int l = 0, r = min(b - a + 1, d - c + 1), ans = 0;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (check(mid, st[d], a, b)) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        printf("%d\n", ans);
    }
    return 0;
}