#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using YangTY::fastIO::is;
using YangTY::fastIO::os;
const int maxn = 1e5 + 5;

int n, m, tot, a[maxn], a0[maxn], pre[maxn];
struct Query {
    int type, x, y, z, sgn, id;
} q[maxn * 5], tmp[maxn * 5];
int ans1[maxn], ans2[maxn];

il bool operator<=(const Query &a, const Query &b) {return make_pair(a.y, a.z) <= make_pair(b.y, b.z);}

struct BIT {
    int t[maxn];
    #define lowbit(x) (x & -x)
    void add(int x, int c) {
        for (; x <= n; x += lowbit(x)) t[x] += c;
        return;
    }
    int query(int x) {
        int ret = 0;
        for (; x; x -= lowbit(x)) ret += t[x];
        return ret;
    }
} tree;

void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1, i = l, j = mid + 1, cnt = 0;
    solve(l, mid), solve(mid + 1, r);
    for (int p = l; p <= r; ) {
        if (i <= mid && (j > r || q[i] <= q[j])) {
            if (q[i].type == 1) tree.add(q[i].z + 1, 1), ++cnt;
            tmp[p++] = q[i++];
        } else {
            if (q[j].type == 2) {
                ans1[q[j].id] += cnt * q[j].sgn;
                ans2[q[j].id] += tree.query(q[j].z + 1) * q[j].sgn;
            }
            tmp[p++] = q[j++];
        }
    }
    FOR(i, l, mid) if (q[i].type == 1) tree.add(q[i].z + 1, -1);
    FOR(i, l, r) q[i] = tmp[i];
    return;
}

int main() {
    is >> n >> m;
    FOR(i, 1, n) is >> a[i], a0[i] = a[i];
    sort(a0 + 1, a0 + n + 1);
    FOR(i, 1, n) {
        a[i] = lower_bound(a0 + 1, a0 + n + 1, a[i]) - a0;
        q[++tot] = {1, i, a[i], pre[a[i]], 0, 0};
        pre[a[i]] = i;
    }
    FOR(i, 1, m) {
        int l, r, A, B; is >> l >> r >> A >> B;
        A = lower_bound(a0 + 1, a0 + n + 1, A) - a0;
        B = upper_bound(a0 + 1, a0 + n + 1, B) - a0 - 1;
        q[++tot] = {2, r, B, l - 1, 1, i};
        q[++tot] = {2, r, A - 1, l - 1, -1, i};
        q[++tot] = {2, l - 1, B, l - 1, -1, i};
        q[++tot] = {2, l - 1, A - 1, l - 1, 1, i};
    }
    stable_sort(q + 1, q + tot + 1, [](const Query &a, const Query &b) {return make_tuple(a.x, a.y, a.z) < make_tuple(b.x, b.y, b.z);});
    solve(1, tot);
    FOR(i, 1, m) os << ans1[i] << ' ' << ans2[i] << '\n';
    return 0;
}