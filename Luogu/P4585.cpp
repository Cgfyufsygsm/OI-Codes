#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
namespace fastIO {
const int maxc = 1 << 23;
char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
template<typename T> void read(T &n) {
    int x = 0; n = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        n = n * 10 + c - '0', c = getchar();
    n = x ? -n : n;
}
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e5 + 5, LG = 17;
int n, m, day, ans[maxn], sp[maxn];

struct Operation {
    int op, t, s, v;
    int l, r, tl, tr, x;
} op[maxn];

struct Trie {
    int root[maxn], tot;

    struct node {
        int ch[2], size;
        node() {ch[0] = ch[1] = size = 0;}
    } t[maxn * 25];

    int clone(int u) {
        t[++tot] = t[u];
        return tot;
    }

    int insert0(int u, int k, int val) {
        u = clone(u);
        ++t[u].size;
        int c = (val >> k) & 1;
        if (~k) t[u].ch[c] = insert0(t[u].ch[c], k - 1, val);
        return u;
    }

    int query(int l, int r, int k, int val) {
        if (k < 0) return 0;
        int c = (val >> k) & 1;
        if (t[t[r].ch[c ^ 1]].size - t[t[l].ch[c ^ 1]].size)
            return query(t[l].ch[c ^ 1], t[r].ch[c ^ 1], k - 1, val) | (1 << k);
        return query(t[l].ch[c], t[r].ch[c], k - 1, val);
    }

    void insert(int pre, int id, int val) {
        root[id] = insert0(root[pre], LG, val);
        return;
    }

    int query(int l, int r, int val) {
        return query(root[l - 1], root[r], LG, val);
    }
} t1, t0;

struct Query {
    int id, l, r, x;
};

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

struct SegmentTree {
    vector<pair<int, int> > goods;
    vector<Query> vecQ;
} t[maxn << 2];

void insertGoods(int i, int j, int k, int x, int s, int v) {
    t[k].goods.push_back({s, v});
    if (i == j) return;
    if (x <= M) insertGoods(i, M, L, x, s, v);
    else insertGoods(M + 1, j, R, x, s, v);
    return;
}

void insertQuery(int i, int j, int k, int l, int r, Query q) {
    if (l <= i && r >= j) {
        t[k].vecQ.push_back(q);
        return;
    }
    if (l <= M) insertQuery(i, M, L, l, r, q);
    if (r > M) insertQuery(M + 1, j, R, l, r, q);
    return;
}

int shopCnt, shop[maxn];

void insert(int k) {
    sort(t[k].goods.begin(), t[k].goods.end());
    shopCnt = 0;
    if (!t[k].goods.empty()) {
        shop[shopCnt = 1] = t[k].goods[0].first;
        t1.insert(0, 1, t[k].goods[0].second);
    }
    for (int i = 1; i < (int)t[k].goods.size(); ++i) {
        bool flg = 0;
        if (t[k].goods[i].first != t[k].goods[i - 1].first) {
            flg = 1;
            shop[++shopCnt] = t[k].goods[i].first;
        }
        t1.insert(shopCnt - flg, shopCnt, t[k].goods[i].second);
    }
    return;
}

void clear(int k) {
    FOR(i, 1, t[k].goods.size()) t1.root[i] = 0;
    t1.tot = 0;
    return;
}

void dfs(int i, int j, int k) {
    insert(k);
    for (Query q : t[k].vecQ) {
        int l = q.l, r = q.r;
        l = lower_bound(shop + 1, shop + shopCnt + 1, l) - shop;
        r = lower_bound(shop + 1, shop + shopCnt + 1, r) - shop;
        if (shop[r] > q.r || r > shopCnt) --r;
        if (l <= r) chkmax(ans[q.id], t1.query(l, r, q.x));
    }
    clear(k);
    if (i == j) return;
    dfs(i, M, L), dfs(M + 1, j, R);
    return;
}

int main() {
    read(n, m);
    FOR(i, 1, n) read(sp[i]), t0.insert(i - 1, i, sp[i]);
    FOR(i, 1, m) {
        read(op[i].op);
        if (op[i].op == 0) {
            op[i].t = ++day;
            read(op[i].s, op[i].v);
        } else {
            op[i].t = i == 1 ? ++day : day;
            read(op[i].l, op[i].r, op[i].x, op[i].tr);
            op[i].tl = day - op[i].tr + 1, op[i].tr = day;
            ans[i] = t0.query(op[i].l, op[i].r, op[i].x);
        }
    }
    FOR(i, 1, m) {
        if (op[i].op == 0) {
            insertGoods(1, day, 1, op[i].t, op[i].s, op[i].v);
        } else {
            if (op[i].tl > op[i].tr) continue;
            Query q = (Query){i, op[i].l, op[i].r, op[i].x};
            insertQuery(1, day, 1, op[i].tl, op[i].tr, q);
        }
    }
    dfs(1, day, 1);
    FOR(i, 1, m) if (op[i].op) print(ans[i]);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}