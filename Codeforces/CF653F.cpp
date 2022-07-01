#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 5e5 + 5;
char s[maxn];

struct SAM {
    int ch[2], fa, len;
} sam[maxn << 1];
int n, stk[maxn], top, las = 1, totSAM = 1;

struct Node {
    int ch[2];
    ll sum;
} t[maxn * 60];
int tot, rt[maxn];

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define M ((i + j) >> 1)

void insert(int &k, int i, int j, int x) {
    if (!k) k = ++tot;
    ++t[k].sum;
    if (i == j) return;
    if (x <= M) insert(ls(k), i, M, x);
    else insert(rs(k), M + 1, j, x);
    return;
}

int query(int k, int i, int j, int x, int y) {
    if (!k || x > y) return 0;
    if (x <= i && y >= j) return t[k].sum;
    int ret = 0;
    if (x <= M) ret += query(ls(k), i, M, x, y);
    if (y > M) ret += query(rs(k), M + 1, j, x, y);
    return ret;
}

ll ans;

void extend(int id) {
    int cur = ++totSAM, c = s[id] - '(';
    sam[cur].len = sam[las].len + 1;
    int p = las;
    while (p && !sam[p].ch[c]) sam[p].ch[c] = cur, p = sam[p].fa;
    if (!p) sam[cur].fa = 1;
    else {
        int q = sam[p].ch[c];
        if (sam[q].len == sam[p].len + 1) sam[cur].fa = q;
        else {
            int clone = ++totSAM;
            sam[clone] = sam[q];
            sam[clone].len = sam[p].len + 1;
            while (p && sam[p].ch[c] == q) sam[p].ch[c] = clone, p = sam[p].fa;
            sam[q].fa = sam[cur].fa = clone;
        }
    }
    las = cur;
    if (!c) {
        stk[++top] = id;
        insert(rt[top], 1, n, id);
    } else {
        if (!top) {
            stk[0] = id;
            return;
        }
        int l = max(1, stk[top - 1]);
        ans += query(rt[top--], 1, n, l, id - sam[sam[cur].fa].len);
    }
    return;
}

int main() {
    scanf("%d", &n);
    scanf("%s", s + 1);
    FOR(i, 1, n) extend(i);
    printf("%lld\n", ans);
    return 0;
}