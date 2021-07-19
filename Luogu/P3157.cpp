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

typedef long long ll;
const int maxn = 1e5 + 5;

struct node {
    int pos, t, val;
    il bool operator<(const node &b) const {return pos == b.pos ? val < b.val : pos < b.pos;}
} a[maxn], tmp[maxn];

il bool cmp(const node &a, const node &b) {return a.t < b.t;}

int n, m;
ll ans[maxn];

struct BIT {
    int T[maxn];
    void add(int x, int v) {
        for (; x <= n; x += lowbit(x))
            T[x] += v;
        return;
    }
    int ask(int x) {
        int ret = 0;
        for (; x; x -= lowbit(x))
            ret += T[x];
        return ret;
    }
    void clear(int x) {
        for (; x <= n; x += lowbit(x))
            T[x] = 0;
        return;
    }
} tree;

void solve(int l, int r) {
    if (l >= r) return;
    int m = (l + r) >> 1;
    solve(l, m), solve(m + 1, r);
    for (int i = l, j = m + 1, cnt = l; i <= m || j <= r;) {
        if (j > r || (i <= m && a[i] < a[j]))
            tree.add(a[i].val, 1), tmp[cnt++] = a[i++];
        else ans[a[j].t] += tree.ask(n) - tree.ask(a[j].val), tmp[cnt++] = a[j++];
    }
    FOR(i, l, r) tree.clear(a[i].val);
    FOR(i, l, r) a[i] = tmp[i];
    DEC(i, r, l)
        if (a[i].t <= m) tree.add(a[i].val, 1);
        else ans[a[i].t] += tree.ask(a[i].val);
    FOR(i, l, r) tree.clear(a[i].val);
    return;
}

int main() {
    n = read(), m = read();
    FOR(i, 1, n) {
        int tmp = read();
        a[tmp].val = tmp, a[tmp].pos = i;
    }
    int T = n;
    FOR(i, 1, m) a[read()].t = T--;
    FOR(i, 1, n)
        if (!a[i].t) a[i].t = T--;
    std::sort(a + 1, a + n + 1, cmp);
    solve(1, n);
    FOR(i, 1, n) ans[i] += ans[i - 1];
    DEC(i, n, n - m + 1) printf("%lld\n", ans[i]);
    return 0;
}