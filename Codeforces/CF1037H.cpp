#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e5 + 5;

struct SGT {
    int ch[maxn * 25][2], sum[maxn * 25], tot;
    #define ls(u) ch[u][0]
    #define rs(u) ch[u][1]
    #define M ((i + j) >> 1)
    void insert(int &u, int i, int j, int x) {
        if (!u) u = ++tot;
        ++sum[u];
        if (i == j) return;
        if (x <= M) insert(ls(u), i, M, x);
        else insert(rs(u), M + 1, j, x);
        return;
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
        sum[u] = sum[u1] + sum[u2];
        return u;
    }
    int query(int u, int i, int j, int x, int y) {
        if (!u) return 0;
        if (x <= i && y >= j) return sum[u];
        int ret = 0;
        if (x <= M) ret += query(ls(u), i, M, x, y);
        if (y > M) ret += query(rs(u), M + 1, j, x, y);
        return ret;
    }
    #undef ls
    #undef rs
    #undef M
} sgt;

int root[maxn], n;
char s[maxn], t[maxn];

struct SAM {
    int ch[maxn][26], fa[maxn], len[maxn], tot, las;
    char res[maxn]; int resLen;
    int head[maxn], to[maxn], nxt[maxn], cnte;
    SAM() {
        tot = las = 1;
    }
    il void addEdge(int u, int v) {
        to[++cnte] = v;
        nxt[cnte] = head[u];
        head[u] = cnte;
        return;
    }
    void extend(int c, int x) {
        int cur = ++tot;
        len[cur] = len[las] + 1;
        int p = las;
        while (p && !ch[p][c]) ch[p][c] = cur, p = fa[p];
        if (!p) fa[cur] = 1;
        else {
            int q = ch[p][c];
            if (len[q] == len[p] + 1) fa[cur] = q;
            else {
                int clone = ++tot;
                memcpy(ch[clone], ch[q], sizeof ch[q]);
                len[clone] = len[p] + 1, fa[clone] = fa[q];
                while (p && ch[p][c] == q) ch[p][c] = clone, p = fa[p];
                fa[cur] = fa[q] = clone;
            }
        }
        sgt.insert(root[cur], 1, n, x);
        las = cur;
        return;
    }
    void dfs(int u) {
        for (int i = head[u]; i; i = nxt[i]) {
            int &v = to[i];
            dfs(v);
            root[u] = sgt.merge(root[u], root[v], 1, n);
        }
        return;
    }
    void build() {
        FOR(i, 2, tot) addEdge(fa[i], i);
        dfs(1);
        return;
    }
    bool match(int u, char *t, int l, int r, int cur, int totLen) {
        int c = 0;
        if (cur > totLen) c = -1;
        else c = t[cur] - 'a';
        if (c >= 0 && ch[u][c] && sgt.query(root[ch[u][c]], 1, n, l + cur - 1, r) && match(ch[u][c], t, l, r, cur + 1, totLen)) {
            res[++resLen] = c + 'a';
            return true;
        }
        FOR(i, c + 1, 25) if (ch[u][i] && sgt.query(root[ch[u][i]], 1, n, l + cur - 1, r)) {
            res[++resLen] = i + 'a';
            return true;
        }
        return false;
    }
    bool match(char *t, int l, int r) {
        resLen = 0;
        if (match(1, t, l, r, 1, strlen(t + 1))) {
            reverse(res + 1, res + resLen + 1);
            res[resLen + 1] = '\0';
            return true;
        } else return false;
    }
} sam;

int main() {
    scanf("%s", s + 1);
    n = strlen(s + 1);
    FOR(i, 1, n) sam.extend(s[i] - 'a', i);
    sam.build();
    int q; scanf("%d", &q);
    while (q--) {
        int l, r; scanf("%d %d", &l, &r);
        scanf("%s", t + 1);
        if (sam.match(t, l, r)) puts(sam.res + 1);
        else puts("-1");
    }
    return 0;
}