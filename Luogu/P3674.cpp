#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using YangTY::fastIO::is;
using YangTY::fastIO::os;
const int maxn = 1e5 + 5, N = 1e5;
int a[maxn], n, m, ans[maxn], block, cnt[maxn];
bitset<maxn << 1> S, rS;

struct Query {
    int type, l, r, x, id;
} q[maxn];

il void add(int id) {
    if (++cnt[a[id]] == 1) S.set(a[id]), rS.set(N - a[id]);
    return;
}

il void del(int id) {
    if (!--cnt[a[id]]) S.reset(a[id]), rS.reset(N - a[id]);
    return;
}

int main() {
    is >> n >> m;
    block = n / (sqrt(m) + 1) + 1;
    FOR(i, 1, n) is >> a[i];
    FOR(i, 1, m) is >> q[i].type >> q[i].l >> q[i].r >> q[i].x, q[i].id = i;
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {return ((a.l / block) ^ (b.l / block)) ? a.l < b.l : (((a.l / block) & 1) ? a.r > b.r : a.r < b.r);});
    int l = 1, r = 0;
    FOR(i, 1, m) {
        while (r < q[i].r) add(++r);
        while (l > q[i].l) add(--l);
        while (r > q[i].r) del(r--);
        while (l < q[i].l) del(l++);
        if (q[i].type == 1) ans[q[i].id] = (S & (S << q[i].x)).any();
        else if (q[i].type == 2) ans[q[i].id] = (S & (rS >> (N - q[i].x))).any();
        else {
            for (int j = 1; j * j <= q[i].x; ++j) if (!(q[i].x % j)) {
                if (S.test(j) && S.test(q[i].x / j)) {
                    ans[q[i].id] = 1;
                    break;
                }
            }
        }
    }
    FOR(i, 1, m) os << (ans[i] ? "hana" : "bi") << '\n';
    return 0;
}