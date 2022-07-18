#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e6 + 100, N = 2e6 + 50;
int a[maxn], n, q;

int sum[maxn << 2], tag[maxn << 2];
#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

il void pushUp(int k) {
    sum[k] = sum[L] + sum[R];
    return;
}

il void pushTag(int i, int j, int k, int t) {
    tag[k] = t;
    sum[k] = (j - i + 1) * t;
    return;
}

il void pushDown(int i, int j, int k) {
    if (tag[k] == -1) return;
    pushTag(i, M, L, tag[k]), pushTag(M + 1, j, R, tag[k]);
    tag[k] = -1;
}

int query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return sum[k];
    pushDown(i, j, k);
    int ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret += query(M + 1, j, R, x, y);
    return ret;
}

int queryNxt0(int i, int j, int k, int x) {
    if (i == j) return sum[k] == 1 ? 0 : i;
    pushDown(i, j, k);
    if (i >= x) {
        if (sum[k] == j - i + 1) return 0;
        if (sum[L] == M - i + 1) return queryNxt0(M + 1, j, R, x);
        else return queryNxt0(i, M, L, x);
    }
    if (x > M) return queryNxt0(M + 1, j, R, x);
    int ret = queryNxt0(i, M, L, x);
    return ret ? ret : queryNxt0(M + 1, j, R, x);
}

int queryNxt1(int i, int j, int k, int x) {
    if (i == j) return sum[k] == 1 ? i : 0;
    pushDown(i, j, k);
    if (i >= x) {
        if (!sum[k]) return 0;
        if (!sum[L]) return queryNxt1(M + 1, j, R, x);
        else return queryNxt1(i, M, L, x);
    }
    if (x > M) return queryNxt1(M + 1, j, R, x);
    int ret = queryNxt1(i, M, L, x);
    return ret ? ret : queryNxt1(M + 1, j, R, x);
}

void modify(int i, int j, int k, int x, int y, int c) {
    if (x <= i && y >= j) return pushTag(i, j, k, c);
    pushDown(i, j, k);
    if (x <= M) modify(i, M, L, x, y, c);
    if (y > M) modify(M + 1, j, R, x, y, c);
    return pushUp(k);
}

void update(int x, int op) {
    if (op > 0) {
        if (!query(1, N, 1, x, x)) modify(1, N, 1, x, x, 1);
        else {
            int pos = queryNxt0(1, N, 1, x);
            modify(1, N, 1, x, pos - 1, 0), modify(1, N, 1, pos, pos, 1);
        }
    } else {
        if (query(1, N, 1, x, x)) modify(1, N, 1, x, x, 0);
        else {
            int pos = queryNxt1(1, N, 1, x);
            modify(1, N, 1, x, pos - 1, 1), modify(1, N, 1, pos, pos, 0);
        }
    }
    return;
}

int getAns(int i, int j, int k) {
    if (i == j) return i;
    pushDown(i, j, k);
    if (sum[R]) return getAns(M + 1, j, R);
    else return getAns(i, M, L);
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> q;
    memset(tag, -1, sizeof tag);
    FOR(i, 1, n) cin >> a[i], update(a[i], 1);
    while (q--) {
        int k, l; cin >> k >> l;
        update(a[k], -1);
        update(a[k] = l, 1);
        cout << getAns(1, N, 1) << '\n';
    }
    return 0;
}