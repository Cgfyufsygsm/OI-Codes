#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read() {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

const int maxn = 1e6 + 5;

int n, m, a[maxn], cnt[maxn], ans[maxn], block, tmp;

struct node {
    int l, l1, r, id;
    il bool operator<(const node &b) {return (l / block) ^ (b.l / block) ? l < b.l : (((l / block) & 1) ? r < b.r : r > b.r);}
} q[maxn];

void add(int x) {
    if (++cnt[a[x]] == 1) ++tmp;
    return;
}

void del(int x) {
    if (!--cnt[a[x]]) --tmp;
    return;
}

int main() {
    n = read();
    FOR(i, 1, n) a[i] = read();
    m = read();
    block = n / sqrt(m * 2 / 3);
    FOR(i, 1, m) q[i].l = read(), q[i].r = read(), q[i].id = i;
    std::sort(q + 1, q + m + 1);
    int l = 0, r = 0;
    FOR(i, 1, m) {
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        ans[q[i].id] = tmp;
    }
    FOR(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}