#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;
const int maxn = 6e5 + 5;
int n, m, tot;
ll a[maxn], rt[maxn], ans[maxn];

struct operation {
    int op;
    ll t, i, k;
} q[maxn];

struct line {
    ll k, b, t1, t2;//维护时间的编号
    line() {k = b = t1 = 0, t2 = maxn;}
} L[maxn << 2];

int head[maxn], cnt, t[maxn << 2];

il int find(ll t) {return std::lower_bound(rt + 1, rt + tot + 1, t) - rt;}
il ll calc(ll X, int i) {return L[i].k * X + L[i].b;}
il ll max(ll a, ll b) {return a > b ? a : b;}

#define ls (k << 1)
#define rs (ls | 1)
#define M ((i + j) >> 1)

void update(int k, int i, int j, int x, int y, int u) {
    if (x > j || y < i) return;
    int v = t[k];
    ll resu = calc(rt[M], u), resv = calc(rt[M], v);
    if (x <= i && y >= j) {
        if (i == j) {
            if (resu > resv) t[k] = u;
            return;
        }
        if (L[u].k > L[v].k) {
            if (resu > resv)
                t[k] = u, update(ls, i, M, x, y, v);
            else update(rs, M + 1, j, x, y, u);
        } else if (L[u].k < L[v].k) {
            if (resu > resv)
                t[k] = u, update(rs, M + 1, j, x, y, v);
            else update(ls, i, M, x, y, u);
        } else if (resu > resv) t[k] = u;
        return;
    }
    update(ls, i, M, x, y, u);
    update(rs, M + 1, j, x, y, u);
    return;
}

ll query(int k, int i, int j, int x) {
    ll ret = calc(rt[x], t[k]);
    if (i >= j) return ret;
    if (x <= M) ret = max(ret, query(ls, i, M, x));
    else ret = max(ret, query(rs, M + 1, j, x));
    return ret;
}

int main() {
    scanf("%d %d", &n, &m);
    FOR(i, 1, n) scanf("%lld", a + i), head[i] = ++cnt, L[cnt].t1 = 1, L[cnt].b = a[i];
    char tmp[10];
    rt[++tot] = 0;
    FOR(i, 1, m) {
        scanf("%lld", &q[i].t), rt[++tot] = q[i].t;
        scanf("%s", tmp);
        if (tmp[0] == 'q') q[i].op = 1;
        else scanf("%lld %lld", &q[i].i, &q[i].k);
    }
    tot = std::unique(rt + 1, rt + tot + 1) - rt - 1;
    FOR(i, 1, m) {
        if (q[i].op == 0) {
            q[i].t = find(q[i].t);
            line &last = L[head[q[i].i]], now;
            last.t2 = q[i].t;
            ll y = last.k * rt[last.t2] + last.b;
            now.k = q[i].k, now.t1 = q[i].t;
            now.b = y - now.k * rt[now.t1];
            L[++cnt] = now, head[q[i].i] = cnt;
        }
        else q[i].t = find(q[i].t);
    }
    FOR(i, 1, n) L[head[i]].t2 = tot;
    FOR(i, 1, cnt) update(1, 1, tot, L[i].t1, L[i].t2, i);
    FOR(i, 1, m) if (q[i].op == 1) ans[i] = query(1, 1, tot, q[i].t);
    memset(t, 0, sizeof t);
    FOR(i, 1, cnt) L[i].k *= -1ll, L[i].b *= -1ll, update(1, 1, tot, L[i].t1, L[i].t2, i);
    FOR(i, 1, m) if (q[i].op == 1) printf("%lld\n", max(ans[i], query(1, 1, tot, q[i].t)));
    return 0;
}