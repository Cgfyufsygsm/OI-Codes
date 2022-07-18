#include <bits/stdc++.h>
#include <fastio.hpp>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using YangTY::fastIO::is;
using YangTY::fastIO::os;
using ll = long long;
const int maxn = 1e5 + 5, block = 300;
int n, m, a[maxn], a0[maxn], bel[maxn], L[maxn], R[maxn];

struct DS {
    int sum1[maxn], sum2[maxn]; // 维护小于 x 的数的个数
    void init() {
        memset(sum1, 0, sizeof sum1);
        memset(sum2, 0, sizeof sum2);
        return;
    }
    void insert(int x) {
        FOR(i, bel[x] + 1, bel[n]) ++sum1[i];
        FOR(i, x + 1, R[bel[x]]) ++sum2[i];
    }
    int query(int x) {return sum1[bel[x]] + sum2[x];}
} ds;

struct Query {
    int l, r, id; ll ans;
} q[maxn];
ll pref[maxn], preg[maxn], ans[maxn];
vector<tuple<int, int, int, int>> v[maxn];

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a[i], a0[i] = a[i];
    sort(a0 + 1, a0 + n + 1);
    int tota = unique(a0 + 1, a0 + n + 1) - a0 - 1;
    FOR(i, 1, n) {
        a[i] = lower_bound(a0 + 1, a0 + tota + 1, a[i]) - a0;
        bel[i] = (i - 1) / block + 1;
    }
    FOR(i, 1, bel[n]) L[i] = (i - 1) * block + 1, R[i] = min(n, i * block);
    FOR(i, 1, n) {
        pref[i] = ds.query(a[i]); // [1, i - 1] 中比 a_i 小的
        preg[i] = i - 1 - ds.query(a[i] + 1); // [1, i - 1] 中比 a_i 大的
        ds.insert(a[i]);
    }
    ds.init();
    FOR(i, 1, m) is >> q[i].l >> q[i].r, q[i].id = i;
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {return (bel[a.l] ^ bel[b.l]) ? a.l < b.l : a.r < b.r;});
    for (int i = 1, l = 1, r = 0; i <= m; ++i) {
        if (l < q[i].l) v[r].emplace_back(l, q[i].l - 1, -i, 0);
        while (l < q[i].l) q[i].ans += pref[l++];
        if (l > q[i].l) v[r].emplace_back(q[i].l, l - 1, i, 0);
        while (l > q[i].l) q[i].ans -= pref[--l];
        if (r < q[i].r) v[l - 1].emplace_back(r + 1, q[i].r, -i, 1);
        while (r < q[i].r) q[i].ans += preg[++r];
        if (r > q[i].r) v[l - 1].emplace_back(q[i].r + 1, r, i, 1);
        while (r > q[i].r) q[i].ans -= preg[r--];
    }
    for (int i = 1, l, r, id, op; i <= n; ++i) {
        ds.insert(a[i]);
        for (const auto &x : v[i]) {
            tie(l, r, id, op) = x;
            ll tmp = 0;
            for (int j = l; j <= r; ++j) {
                if (!op) tmp = ds.query(a[j]);
                else tmp = i - ds.query(a[j] + 1);
                if (id < 0) q[-id].ans -= tmp;
                else q[id].ans += tmp;
            }
        }
    }
    FOR(i, 1, m) q[i].ans += q[i - 1].ans, ans[q[i].id] = q[i].ans;
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}