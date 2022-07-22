#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using namespace YangTY::fastIO;
using ll = long long;
const int maxn = 1e5 + 5, B = 317;
int n, m, a[maxn], _a[maxn]; // _a: sorted a
struct Node {int id, x;} b[maxn];
int bel[maxn], st[maxn], ed[maxn], pos[maxn];
int pre[maxn], suf[maxn], ts[maxn], s[B + 5][maxn], g[B + 5][maxn];
int sum[maxn], insum[maxn], w[maxn], w2[maxn];
ll t[B + 5][B + 5];

il void modify(int x, int k) {
    FOR(i, bel[x], bel[n]) sum[i] += k;
    FOR(i, x, ed[bel[x]]) insum[i] += k;
    return;
}

il int query(int x) {
    return sum[bel[x] - 1] + insum[x];
}

void prework(int id) {
    int tmp = 0;
    FOR(i, st[id], ed[id]) w[++tmp] = a[i];
    sort(w + 1, w + tmp + 1);
    for (int i = 1, j = 0; i <= n; ++i) {
        while (j < tmp && w[j + 1] < b[i].x) ++j;
        s[id][b[i].id] = j;
    }
    FOR(i, st[id], ed[id]) _a[i] = w[i - st[id] + 1];
    DEC(i, ed[id] + 1, st[id] + 1) {
        if (i <= ed[id]) modify(a[i], 1);
        FOR(j, st[id], i - 1) g[i - st[id] - 1][j] = ts[j] - query(a[j]);
    }
    FOR(i, st[id] + 1, ed[id]) modify(a[i], -1);
    return;
}

ll query(int l, int r) {
    ll ret = 0;
    if (bel[l] == bel[r]) {
        FOR(i, l, r) ret += g[r - st[bel[l]]][i];
        return ret;
    }
    int t1 = 0, t2 = 0;
    FOR(i, st[bel[l]], ed[bel[l]]) if (pos[_a[i]] >= l) w[++t1] = _a[i];
    FOR(i, st[bel[r]], ed[bel[r]]) if (pos[_a[i]] <= r) w2[++t2] = _a[i];
    for (int i = 1, j = 0; i <= t1; ++i) {
        while (j < t2 && w2[j + 1] < w[i]) ++j;
        ret += j;
    }
    FOR(i, l, ed[bel[l]]) ret += s[bel[r] - 1][i] - s[bel[l]][i];
    FOR(i, st[bel[r]], r) ret += (st[bel[r]] - ed[bel[l]] - 1) - (s[bel[r] - 1][i] - s[bel[l]][i]);
    FOR(i, bel[l] + 1, bel[r] - 1) ret += t[i][bel[r] - 1] - t[i][i] + pre[ed[i]];
    return ret + suf[l] + pre[r];
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a[i], b[i] = {i, a[i]}, pos[a[i]] = i;
    sort(b + 1, b + n + 1, [](const Node &a, const Node &b) {return a.x < b.x;});
    FOR(i, 1, n) bel[i] = i / B + 1, ed[bel[i]] = i;
    DEC(i, n, 1) st[bel[i]] = i;
    FOR(i, 1, bel[n]) {
        FOR(j, st[i], ed[i]) pre[j] = (j == st[i] ? 0 : pre[j - 1]) + (j - st[i] - query(a[j])), modify(a[j], 1);
        FOR(j, st[i], ed[i]) modify(a[j], -1);
        DEC(j, ed[i], st[i]) suf[j] = (j == ed[i] ? 0 : suf[j + 1]) + (ts[j] = query(a[j])), modify(a[j], 1);
        DEC(j, ed[i], st[i]) modify(a[j], -1);
    }
    FOR(i, 1, bel[n]) prework(i);
    FOR(j, 1, bel[n]) FOR(i, 1, n) s[j][i] += s[j - 1][i], t[bel[i]][j] += s[j][i];
    ll las = 0, l, r;
    while (m--) {
        is >> l >> r;
        os << (las = query(l ^ las, r ^ las)) << '\n';
    }
    return 0;
}