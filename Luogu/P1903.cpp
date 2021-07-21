#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1e7 + 5;
    char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
    typedef int IO_int;
    il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
    IO_int read() {
        IO_int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
    char readC() {
        char c = getchar();
        while (!isalpha(c)) c = getchar();
        return c;
    }
    char obuf[maxc], *__pO = obuf;
    il void putchar(char c) {*__pO++ = c;}
    void print(IO_int x) {
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

const int maxn = 1.5e5 + 5, maxv = 1e6 + 5;
int n, m, totq, totc, a[maxn], block, ans[maxn];

int cnt[maxv], tmp;

struct node {
    int l, r, t, pos, val, id;
} q[maxn], c[maxn];

il bool cmp(const node &a, const node &b) {
    if ((a.l / block) ^ (b.l / block)) return a.l / block < b.l / block;
    if ((a.r / block) ^ (b.r / block)) return a.r / block < b.r / block;
    return a.t < b.t;
}

il void add(int x) {
    if (!cnt[a[x]]++)
        ++tmp;
    return;
}

il void del(int x) {
    if (!--cnt[a[x]])
        --tmp;
    return;
}

void work(int t, int i) {
    if (c[t].pos >= q[i].l && c[t].pos <= q[i].r) {
        if (!cnt[c[t].val]++)
            ++tmp;
        if (!--cnt[a[c[t].pos]])
            --tmp;
    }
    std::swap(c[t].val, a[c[t].pos]);
    return;
}

int main() {
    n = read(), m = read();
    FOR(i, 1, n) a[i] = read();
    FOR(i, 1, m) {
        char x = readC();
        if (x == 'Q') {
            ++totq;
            q[totq].l = read(), q[totq].r = read(), q[totq].t = totc, q[totq].id = totq;
        } else {
            ++totc;
            c[totc].pos = read(), c[totc].val = read();
        }
    }
    block = pow(n, 2.0 / 3.0);
    std::sort(q + 1, q + totq + 1, cmp);
    int now = 0, l = 1, r = 0;
    FOR(i, 1, totq) {
        while (l < q[i].l) del(l++);
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (r > q[i].r) del(r--);

        while (now < q[i].t) work(++now, i);
        while (now > q[i].t) work(now--, i);

        ans[q[i].id] = tmp;
    }
    FOR(i, 1, totq) print(ans[i]), putchar('\n');
    return output(), 0;
}