#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}

using YangTY::fastIO::is;
using YangTY::fastIO::os;
using ll = long long;
const int maxn = 5e5 + 5, block = 800;
int n, m, a[maxn], pos[maxn], bel[maxn], lpos[maxn], rpos[maxn];
ll ans[maxn];

struct Query {
    int l, r, id;
} q[maxn];

struct Chain {
    int pre[maxn], nxt[maxn], stk[maxn], top;
    il int del(int p) {
        int p1 = pre[p], p2 = nxt[p], ret = 0;
        stk[++top] = p;
        if (p1 && p2) ret += myabs(pos[p1] - pos[p2]);
        if (p1) ret -= myabs(pos[p] - pos[p1]);
        if (p2) ret -= myabs(pos[p] - pos[p2]);
        nxt[p1] = p2, pre[p2] = p1;
        return ret;
    }
    void init() {
        FOR(i, 1, n) nxt[i] = i + 1, pre[i] = i - 1;
        nxt[n] = 0;
        return;
    }
    il void undo() {
        int p = stk[top--];
        nxt[pre[p]] = pre[nxt[p]] = p;
        return;
    }
} chain;

int main() {
    is >> n >> m;
    FOR(i, 1, n) {
        is >> a[i];
        pos[a[i]] = i;
        bel[i] = (i - 1) / block + 1;
    }
    FOR(i, 1, bel[n]) lpos[i] = (i - 1) * block + 1, rpos[i] = min(n, i * block);
    FOR(i, 1, m) is >> q[i].l >> q[i].r, q[i].id = i;
    sort(q + 1, q + m + 1, [](const Query &a, const Query &b) {return (bel[a.l] != bel[b.l]) ? a.l < b.l : a.r > b.r;});
    chain.init();
    int l = 1, r = n, lastBlk = 1;
    ll tmp = 0, tmp0 = 0;
    FOR(i, 2, n) tmp += myabs(pos[i] - pos[i - 1]);
    tmp0 = tmp;
    FOR(i, 1, m) {
        if (bel[q[i].l] != lastBlk) {
            while (chain.top) chain.undo();
            while (l < lpos[bel[q[i].l]]) tmp0 += chain.del(a[l++]);
            tmp = tmp0, r = n, lastBlk = bel[q[i].l], chain.top = 0;
        }
        while (r > q[i].r) tmp += chain.del(a[r--]);
        ll cur = tmp, _l = l;
        while (_l < q[i].l) cur += chain.del(a[_l++]);
        while (_l-- > l) chain.undo();
        ans[q[i].id] = cur;
    }
    FOR(i, 1, m) os << ans[i] << '\n';
    return 0;
}