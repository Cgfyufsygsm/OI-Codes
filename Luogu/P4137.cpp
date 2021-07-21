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

const int maxn = 2e5 + 5;
int n, m, a[maxn], block, cnt[maxn], vis[maxn], v[maxn], ans[maxn];

struct node
{
    int l, r, id;
    il bool operator<(const node &b) const {return (l / block) ^ (b.l / block) ? l < b.l : (((l / block) & 1) ? r > b.r : r < b.r);}
} q[maxn];

il void add(int x) {
    if (!cnt[a[x]]++)
        vis[a[x]] = 1, ++v[a[x] / block];
    return;
}

il void del(int x) {
    if (!--cnt[a[x]])
        vis[a[x]] = 0, --v[a[x] / block];
    return;
}

int main() {
    read(n), read(m), block = sqrt(n);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, m) read(q[i].l), read(q[i].r), q[i].id = i;
    std::sort(q + 1, q + m + 1);
    int l = 1, r = 0;
    FOR(i, 1, m) {
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);

        int ret = 0;
        for (int i = 0; v[i] == block; ++i, ret += block);
        while (cnt[ret]) ++ret;
        ans[q[i].id] = ret;
    }
    FOR(i, 1, m) print(ans[i]), putchar('\n');
    return output(), 0;
}