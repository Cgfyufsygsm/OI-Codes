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

typedef long long ll;

const int maxn = 5e4 + 5;
int n, m, k, a[maxn], cnt[maxn], block;

ll tmp, ans[maxn];

struct node {
    int l, r, id;
    il bool operator<(const node &b) const {return (l / block) ^ (b.l / block) ? l < b.l : ((l / block) & 1) ? r < b.r : r > b.r;}
} q[maxn];

il void add(int x) {
    tmp += 2ll * cnt[a[x]]++ + 1;
    return;
}

il void del(int x) {
    tmp += 1 - 2ll * cnt[a[x]]--;
    return;
}

int main() {
    n = read(), m = read(), k = read();
    FOR(i, 1, n) a[i] = read();
    FOR(i, 1, m) q[i].l = read(), q[i].r = read(), q[i].id = i;
    block = n / sqrt(m * 2 / 3);
    std::sort(q + 1, q + m + 1);
    int l = 1, r = 0;
    FOR(i, 1, m) {
        while (l > q[i].l) add(--l);
        while (r < q[i].r) add(++r);
        while (l < q[i].l) del(l++);
        while (r > q[i].r) del(r--);
        ans[q[i].id] = tmp;
    }
    FOR(i, 1, m) printf("%lld\n", ans[i]);
    return 0;
}