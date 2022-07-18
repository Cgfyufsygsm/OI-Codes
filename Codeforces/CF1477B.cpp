#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 2e5 + 5;
char S[maxn], T[maxn];
int n, m, x[maxn], y[maxn];
struct Node {
    int sum, tag;
} t[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void build(int i, int j, int k) {
    if (i == j) {
        t[k].sum = T[i] - '0';
        t[k].tag = -1;
        return;
    }
    build(i, M, L), build(M + 1, j, R);
    t[k].sum = t[L].sum + t[R].sum;
    t[k].tag = -1;
    return;
}

il void pushTag(int i, int j, int k, int c) {
    t[k].sum = c * (j - i + 1);
    t[k].tag = c;
    return;
}

il void pushDown(int i, int j, int k) {
    if (t[k].tag == -1) return;
    pushTag(i, M, L, t[k].tag), pushTag(M + 1, j, R, t[k].tag);
    t[k].tag = -1;
    return;
}

void modify(int i, int j, int k, int x, int y, int c) {
    if (x <= i && y >= j) return pushTag(i, j, k, c);
    pushDown(i, j, k);
    if (x <= M) modify(i, M, L, x, y, c);
    if (y > M) modify(M + 1, j, R, x, y, c);
    t[k].sum = t[L].sum + t[R].sum;
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k].sum;
    pushDown(i, j, k);
    int ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret += query(M + 1, j, R, x, y);
    return ret;
}

bool check(int i, int j, int k) {
    if (i == j) return t[k].sum == S[i] - '0';
    pushDown(i, j, k);
    return check(i, M, L) && check(M + 1, j, R);
}

int main() {
    int cases; is >> cases;
    while (cases--) {
        is >> n >> m;
        is >> (S + 1) >> (T + 1);
        build(1, n, 1);
        FOR(i, 1, m) is >> x[i] >> y[i];
        bool flg = 1;
        DEC(i, m, 1) {
            int cnt1 = query(1, n, 1, x[i], y[i]), cnt0 = y[i] - x[i] + 1 - cnt1;
            if (cnt1 == cnt0) {flg = 0; break;}
            else if (cnt1 > cnt0) modify(1, n, 1, x[i], y[i], 1);
            else modify(1, n, 1, x[i], y[i], 0);
        }
        os << ((flg && check(1, n, 1)) ? "YES" : "NO") << '\n';
    }
    return 0;
}