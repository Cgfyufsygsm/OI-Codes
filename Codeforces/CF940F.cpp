#include <cstdio>
#include <cctype>
#include <cassert>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1e7 + 5;
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

const int maxn = 1e5 + 5;
int n, m, a[maxn], aa[maxn << 1], tota, block;
int totq, totc;

struct node
{
    int l, r, t, id, pos, val;
} q[maxn], c[maxn];

il bool cmp(const node &a, const node &b) {
    if ((a.l / block) ^ (b.l / block)) return a.l < b.l;
    if ((a.r / block) ^ (b.r / block)) return a.r < b.r;
    return a.t < b.t;
}

int cnt[maxn << 1], cntcnt[maxn], ans[maxn];

il void add(int v) {
    --cntcnt[cnt[v]];
    ++cntcnt[++cnt[v]];
    return;
}

il void del(int v) {
    --cntcnt[cnt[v]];
    ++cntcnt[--cnt[v]];
    return;
}

il void modify(int t, int i) {
    if (c[t].pos >= q[i].l && c[t].pos <= q[i].r) {
        del(a[c[t].pos]), add(c[t].val);
    }
    std::swap(c[t].val, a[c[t].pos]);
}

int getAns() {
    int ans = 1;
    while (cntcnt[ans] > 0) ++ans;
    return ans;
}

int main() {
    read(n), read(m), tota = n, block = pow(n, 2.0 / 3.0);
    FOR(i, 1, n) read(a[i]), aa[i] = a[i];
    FOR(i, 1, m) {
        int op; read(op);
        if (op == 1) {
            ++totq;
            q[totq].t = totc, q[totq].id = totq;
            read(q[totq].l), read(q[totq].r);
        } else {
            ++totc;
            read(c[totc].pos), read(c[totc].val);
            aa[++tota] = c[totc].val;
        }
    }
    std::sort(aa + 1, aa + 1 + tota);
    tota = std::unique(aa + 1, aa + tota + 1) - aa - 1;
    FOR(i, 1, n) a[i] = std::lower_bound(aa + 1, aa + tota + 1, a[i]) - aa;
    FOR(i, 1, totc) c[i].val = std::lower_bound(aa + 1, aa + tota + 1, c[i].val) - aa;

    std::sort(q + 1, q + totq + 1, cmp);

    int now = 0, l = 1, r = 0;
    cntcnt[0] = 1e9;
    FOR(i, 1, totq) {
        while (l > q[i].l) add(a[--l]);
        while (r < q[i].r) add(a[++r]);
        while (l < q[i].l) del(a[l++]);
        while (r > q[i].r) del(a[r--]);

        while (now < q[i].t) modify(++now, i);
        while (now > q[i].t) modify(now--, i);

        ans[q[i].id] = getAns();
    }
    FOR(i, 1, totq) print(ans[i]), putchar('\n');
    return output(), 0;
}