#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

il int max(const int &a, const int &b) {return a > b ? a : b;}
il int min(const int &a, const int &b) {return a < b ? a : b;}

typedef double db;
const db alpha = 0.75;
const int maxn = 2e5 + 5;
int n;

struct point
{
    int x[2], v;
} p[maxn];
int totp;

int rt, type[maxn], cur, sum[maxn], size[maxn], ls[maxn], rs[maxn];
int L[maxn], R[maxn], U[maxn], D[maxn];

void pushup(int k) {
    size[k] = size[ls[k]] + size[rs[k]] + 1;
    sum[k] = sum[ls[k]] + sum[rs[k]] + p[k].v;
    L[k] = R[k] = p[k].x[0];
    U[k] = D[k] = p[k].x[1];
    if (ls[k])
        L[k] = min(L[ls[k]], L[k]), R[k] = max(R[ls[k]], R[k]),
        D[k] = min(D[ls[k]], D[k]), U[k] = max(U[ls[k]], U[k]);
    if (rs[k])
        L[k] = min(L[rs[k]], L[k]), R[k] = max(R[rs[k]], R[k]),
        D[k] = min(D[rs[k]], D[k]), U[k] = max(U[rs[k]], U[k]);
    return;
}

il bool bad(int x) {return alpha * size[x] <= (double)max(size[ls[x]], size[rs[x]]);}

int g[maxn], t;

il bool cmp1(const int &a, const int &b) {return p[a].x[0] < p[b].x[0];}
il bool cmp2(const int &a, const int &b) {return p[a].x[1] < p[b].x[1];}

int build(int l, int r) {
    if (l > r) return 0;
    int mid = (l + r) >> 1;
    db av[2] = {0}, va[2] = {0};
    FOR(d, 0, 1)
        FOR(i, l, r) av[d] += p[g[i]].x[d];
    av[0] /= (r - l + 1), av[1] /= (r - l + 1);
    FOR(d, 0, 1)
        FOR(i, l, r)
            va[d] += (av[d] - p[g[i]].x[d]) * (av[d] - p[g[i]].x[d]);
    if (va[0] > va[1])
        std::nth_element(g + l, g + mid, g + r + 1, cmp1), type[g[mid]] = 0;
    else
        std::nth_element(g + l, g + mid, g + r + 1, cmp2), type[g[mid]] = 1;
    ls[g[mid]] = build(l, mid - 1);
    rs[g[mid]] = build(mid + 1, r);
    pushup(g[mid]);
    return g[mid];
}

void pia(int k) {
    if (!k) return;
    pia(ls[k]);
    g[++t] = k;
    pia(rs[k]);
    return;
}

void rebuild(int &k) {
    t = 0;
    pia(k);
    k = build(1, t);
    return;
}

void insert(int &k, int v) {
    if (!k) {
        k = v;
        pushup(k);
        return;
    }
    if (p[v].x[type[k]] < p[k].x[type[k]])
        insert(ls[k], v);
    else insert(rs[k], v);
    pushup(k);
    if (bad(k)) rebuild(k);
}

int l, r, u, d;

int query(int k) {
    if (!k || l > R[k] || r < L[k] || d > U[k] || u < D[k])
        return 0;
    if (l <= L[k] && r >= R[k] && d <= D[k] && u >= U[k])
        return sum[k];
    int ret = 0;
    if (l <= p[k].x[0] && r >= p[k].x[0] && d <= p[k].x[1] && u >= p[k].x[1])
        ret += p[k].v;
    return query(ls[k]) + ret + query(rs[k]);
}

int main() {
    read(n);
    int last = 0;
    while ("sb") {
        int op;
        read(op);
        if (op == 3) break;
        if (op == 1) {
            ++totp;
            read(p[totp].x[0]), read(p[totp].x[1]), read(p[totp].v);
            p[totp].x[0] ^= last, p[totp].x[1] ^= last, p[totp].v ^= last;
            insert(rt, totp);
        } else {
            read(l), read(d), read(r), read(u);
            l ^= last, d ^= last, r ^= last, u ^= last;
            print(last = query(rt)), putchar('\n');
        }
    }
    return output(), 0;
}