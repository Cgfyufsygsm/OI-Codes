#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define lowbit(x) (x & -x)

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

int t[maxn], last[maxn], n, m, a[maxn], ans[maxn];

void add(int x, int v) {
    for (; x <= n; x += lowbit(x))
        t[x] += v;
    return;
}

int sum(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x))
        ret += t[x];
    return ret;
}

struct node {
    int l, r, id;
    il bool operator<(const node &b) const {return r < b.r;}
} q[maxn];

int main() {
    n = read();
    FOR(i, 1, n) a[i] = read();
    m = read();
    FOR(i, 1, m) q[i].l = read(), q[i].r = read(), q[i].id = i;
    std::sort(q + 1, q + m + 1);
    int p = 1;
    FOR(i, 1, n) {
        if (last[a[i]])
            add(last[a[i]], -1);
        last[a[i]] = i;
        add(i, 1);
        while (p <= m && q[p].r <= i) {
            ans[q[p].id] = sum(q[p].r) - sum(q[p].l - 1);
            ++p;
        }
    }
    FOR(i, 1, m) printf("%d\n", ans[i]);
    return 0;
}