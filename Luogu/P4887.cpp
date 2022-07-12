#include <bits/stdc++.h>
#include <fastio.hpp> 
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using YangTY::fastIO::is;
using YangTY::fastIO::os;
using ll = long long;
const int maxn = 1e5 + 5;
int n, m, k, a[maxn], bl[maxn], block;
vector<int> buc;
ll t[maxn], pre[maxn], ans[maxn];

struct Query {
    int l, r, id;
    Query(int _l = 0, int _r = 0, int _id = 0) :  l(_l), r(_r), id(_id) {}
} q[maxn];
vector<Query> v[maxn];

int main() {
    is >> n >> m >> k;
    block = n / (sqrt(2 * m / 3) + 1) + 1;
    if (k > 14) {
        FOR(i, 1, m) os << "0\n";
        return 0;
    }
    FOR(i, 1, n) is >> a[i], bl[i] = (i - 1) / block + 1;
    FOR(i, 1, m) is >> q[i].l >> q[i].r, q[i].id = i;
    FOR(i, 0, 16384 - 1) if (__builtin_popcount(i) == k) buc.emplace_back(i);
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {return (bl[a.l] == bl[b.l]) ? a.r < b.r : a.l < b.l;});
    FOR(i, 1, n) {
        for (auto &x : buc) ++t[a[i] ^ x];
        pre[i] = t[a[i + 1]];
    }
    memset(t, 0, sizeof t);
    for (int i = 1, l = 1, r = 0; i <= m; ++i) {
        if (r < q[i].r) v[l - 1].emplace_back(r + 1, q[i].r, -i);
        while (r < q[i].r) ans[q[i].id] += pre[r++];
        if (l > q[i].l) v[r].emplace_back(q[i].l, l - 1, i);
        while (l > q[i].l) ans[q[i].id] -= pre[l-- - 2];
        if (r > q[i].r) v[l - 1].emplace_back(q[i].r + 1, r, i);
        while (r > q[i].r) ans[q[i].id] -= pre[r-- - 1];
        if (l < q[i].l) v[r].emplace_back(l, q[i].l - 1, -i);
        while (l < q[i].l) ans[q[i].id] += pre[l++ - 1];
    }
    for (int i = 1, l, r, id; i <= n; ++i) {
        for (auto &x : buc) ++t[a[i] ^ x];
        for (const auto &x : v[i]) {
            l = x.l, r = x.r, id = x.id;
            for (int j = l, tmp = 0; j <= r; ++j) {
                tmp = t[a[j]];
                if (j <= i && k == 0) --tmp;
                if (id < 0) ans[q[-id].id] -= tmp;
                else ans[q[id].id] += tmp;
            }
        }
    }
    FOR(i, 1, m) ans[q[i].id] += ans[q[i - 1].id];
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}