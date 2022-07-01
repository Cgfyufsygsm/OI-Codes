#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
using namespace YangTY::fastIO;
const int maxn = 4e5 + 5;
int M = 1002;
int n, m, s[maxn];

int x[maxn], y[maxn], c[maxn], sa[maxn];

void SA(int n) {
    FOR(i, 1, n) ++c[x[i] = s[i]];
    FOR(i, 1, M) c[i] += c[i - 1];
    DEC(i, n, 1) sa[c[x[i]]--] = i;
    for (int k = 1; k <= n; k <<= 1) {
        int num = 0;
        FOR(i, n - k + 1, n) y[++num] = i;
        FOR(i, 1, n) if (sa[i] > k) y[++num] = sa[i] - k;
        memset(c, 0, sizeof c);
        FOR(i, 1, n) ++c[x[i]];
        FOR(i, 1, M) c[i] += c[i - 1];
        DEC(i, n, 1) sa[c[x[y[i]]]--] = y[i];
        swap(x, y);
        num = 1, x[sa[1]] = 1;
        FOR(i, 2, n) {
            if (y[sa[i]] == y[sa[i - 1]] && y[sa[i] + k] == y[sa[i - 1] + k])
                x[sa[i]] = num;
            else x[sa[i]] = ++num;
        }
        if (num == n) break;
        M = num;
    }
    return;
}

int main() {
    is >> n;
    FOR(i, 1, n) is >> s[i];
    s[n + 1] = 1001;
    is >> m;
    FOR(i, 1, m) is >> s[n + 1 + i];
    SA(n + m + 1);
    int p = 1, q = n + 2;
    while (p <= n && q <= n + m + 1) {
        if (x[p] < x[q]) os << s[p++] << ' ';
        else os << s[q++] << ' ';
    }
    while (p <= n) os << s[p++] << ' ';
    while (q <= n + m + 1) os << s[q++] << ' ';
    return 0;
}