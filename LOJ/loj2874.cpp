#include <cstdio>
#include <cctype>
#include <cmath>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

using ll = long long;
const int maxn = 1e5 + 5;
int bel[maxn], n, m, tot, lpos[maxn], rpos[maxn];
ll val[maxn], a[maxn], ans[maxn], cnt[maxn], cnt2[maxn];

struct node {
    int l, r, id;
} q[maxn];

il bool cmp(const node &a, const node &b) {
    if (bel[a.l] ^ bel[b.l]) return bel[a.l] < bel[b.l];
    return a.r < b.r;
}

void del(int x) {--cnt[a[x]];}
void insert(int x, ll &now) {now = max(now, (++cnt[a[x]]) * val[a[x]]);}

int main() {
    read(n), read(m);
    FOR(i, 1, n) read(val[i]), a[i] = val[i];
    std::sort(val + 1, val + n + 1);
    tot = std::unique(val + 1, val + n + 1) - val - 1;
    FOR(i, 1, n) a[i] = std::lower_bound(val + 1, val + tot + 1, a[i]) - val;

    int block = sqrt(n), T = n / block;
    FOR(i, 1, T) {
        if (i * block > n) break;
        lpos[i] = (i - 1) * block + 1;
        rpos[i] = i * block;
    }
    if (rpos[T] < n) ++T, lpos[T] = rpos[T - 1] + 1, rpos[T] = n;
    FOR(j, 1, T) FOR(i, lpos[j], rpos[j]) bel[i] = j;

    FOR(i, 1, m) read(q[i].l), read(q[i].r), q[i].id = i;
    std::sort(q + 1, q + m + 1, cmp);

    int nowblock = 0, l = 1, r = 0;
    ll nowans;
    FOR(i, 1, m) {
        if (bel[q[i].l] == bel[q[i].r]) {
            FOR(j, q[i].l, q[i].r) ++cnt2[a[j]];
            ll res = 0;
            FOR(j, q[i].l, q[i].r)
                res = max(res, cnt2[a[j]] * val[a[j]]);
            FOR(j, q[i].l, q[i].r) --cnt2[a[j]];
            ans[q[i].id] = res;
            continue;
        }
        if (bel[q[i].l] ^ nowblock) {
            while (r > rpos[bel[q[i].l]]) del(r--);
            while (l < rpos[bel[q[i].l]] + 1) del(l++);
            nowans = 0, nowblock = bel[q[i].l];
        }
        while (r < q[i].r) insert(++r, nowans);
        ll tmp = nowans; int _l = l;
        while (_l > q[i].l) insert(--_l, tmp);
        ans[q[i].id] = tmp;
        while (_l < l) del(_l++);
    }
  
    FOR(i, 1, m) print(ans[i], '\n');
    return output(), 0;
}