#include <cstdio>
#include <cctype>
#include <vector>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 21;
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
    char obuf[maxc], *__pO = obuf;
    il void putchar(char c) {*__pO++ = c;}
    template<typename T> void print(T x) {
        if (x < 0) putchar('-'), print(-x);
        else {
            if (x > 9) print(x / 10);
            putchar(x % 10 + '0');
        }
        return;
    }
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

using namespace fastIO;

const int maxn = 20005;
int n, a[maxn], aa[maxn], tota;
std::vector<int> pos[maxn];//每个数出现的位置集合

struct node {
    int maxv, minv, tag, ls, rs;
    node() {
        maxv = -1e9, minv = 1e9;
        tag = ls = rs = 0;
    }
} t[maxn * 300];

int root[maxn], cnt;

int clone(int k) {
    t[++cnt] = t[k];
    return cnt;
}

#define ls(k) t[k].ls
#define rs(k) t[k].rs
#define M ((i + j) >> 1)

il int max(int a, int b) {return a > b ? a : b;}
il int min(int a, int b) {return a < b ? a : b;}

void pushup(int k) {
    t[k].minv = min(t[ls(k)].minv, t[rs(k)].minv);
    t[k].maxv = max(t[ls(k)].maxv, t[rs(k)].maxv);
    return;
}

void build(int i, int j, int &k) {
    if (!k) k = ++cnt;
    if (j <= i) {
        t[k].maxv = t[k].minv = i;
        return;
    }
    build(i, M, ls(k));
    build(M + 1, j, rs(k));
    pushup(k);
    return;
}

il void add(int k, int val) {
    t[k].tag += val;
    t[k].maxv += val;
    t[k].minv += val;
    return;
}

il void pushdown(int k) {
    if (t[k].tag) {
        if (ls(k)) ls(k) = clone(ls(k)), add(ls(k), t[k].tag);
        if (rs(k)) rs(k) = clone(rs(k)), add(rs(k), t[k].tag);
        t[k].tag = 0;
    }
    return;
}

int modify(int k, int i, int j, int x, int y, int val) {
    k = clone(k);
    if (x <= i && y >= j) {
        add(k, val);
        return k;
    }
    pushdown(k);
    if (x <= M) ls(k) = modify(ls(k), i, M, x, y, val);
    if (y > M) rs(k) = modify(rs(k), M + 1, j, x, y, val);
    pushup(k);
    return k;
}

int query(int i, int j, int k, int x, int y, int op) {
    if (x > y) return op ? -1e9 : 1e9;
    if (x <= i && y >= j) return op ? t[k].maxv : t[k].minv;
    pushdown(k);
    int ret = op ? -1e9 : 1e9;
    if (x <= M)
        ret = op ? max(ret, query(i, M, ls(k), x, y, op)) : min(ret, query(i, M, ls(k), x, y, op));
    if (y > M)
        ret = op ? max(ret, query(M + 1, j, rs(k), x, y, op)) : min(ret, query(M + 1, j, rs(k), x, y, op));
    return ret;
}

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]), aa[i] = a[i];
    std::sort(aa + 1, aa + n + 1);
    tota = n;
    FOR(i, 1, n) a[i] = std::lower_bound(aa + 1, aa + tota + 1, a[i]) - aa, pos[a[i]].push_back(i);

    build(1, n, root[1]);

    FOR(val, 2, tota) {
        root[val] = clone(root[val - 1]);
        for (auto p : pos[val - 1]) {
            root[val] = modify(root[val], 1, n, p, n, -2);
        }
    }

    int q; read(q);
    int last = 0;
    while (q--) {
        int p[4];
        read(p[0]), read(p[1]), read(p[2]), read(p[3]);
        FOR(i, 0, 3) p[i] = (p[i] + last) % n + 1;
        std::sort(p, p + 4);
        int ans = 1, l = 1, r = tota;
        while (l <= r) {
            int mid = (l + r) >> 1;
            int tmp1, tmp2;
            int tmp = (tmp1 = query(1, n, root[mid], p[2], p[3], 1)) - (tmp2 = min(query(1, n, root[mid], max(p[0] - 1, 1), max(p[1] - 1, 1), 0), p[0] - 1 == 0 ? 0 : 1e9));
            if (tmp >= 0) ans = mid, l = mid + 1;
            else r = mid - 1;
        }
        print(last = aa[ans]), putchar('\n');
    }
    return output(), 0;
}