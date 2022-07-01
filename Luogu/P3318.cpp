#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using uint64 = unsigned long long;
const uint64 base = 1331;
const int maxn = 4e6 + 5;
int n, m, totS, totT, ans, len, vis[maxn];
string s[maxn], t[maxn];
uint64 pw[maxn], hsh[maxn];
unordered_map<uint64, int> hashT;

uint64 getHash(string s, int len) {
    uint64 res = 0;
    FOR(i, 0, len - 1) res = base * res + s[i];
    return res;
}

uint64 getHash(int l, int r) {
    return hsh[r] - hsh[l - 1] * pw[r - l + 1];
}

int solve(string &s, int id) {
    int ret = 0;
    string tmp = "?" + s.substr(0, len) + s.substr(0, len);
    FOR(i, 1, len << 1) hsh[i] = hsh[i - 1] * base + tmp[i];
    uint64 hshVal = getHash(s.substr(len, n - len), n - len);
    unordered_set<uint64> vis;
    for (int i = 1, j = len; i <= len; ++i, ++j) {
        uint64 cur = getHash(i, j);
        if (vis.count(cur)) continue;
        vis.insert(cur);
        if (getHash(i, i + n - len - 1) == hshVal)
            ret += hashT[getHash(i + n - len, j)];
    }
    return ret;
}

int main() {
    ios::sync_with_stdio(false);
    pw[0] = 1;
    FOR(i, 1, (int)4e6) pw[i] = pw[i - 1] * base;
    cin >> totS >> totT >> n >> m;
    if (n < m) swap(totS, totT), swap(n, m);
    len = (n + m) >> 1;
    FOR(i, 1, totS) cin >> s[i];
    FOR(i, 1, totT) {
        cin >> t[i];
        ++hashT[getHash(t[i], m)];
    }
    FOR(i, 1, totS) ans += solve(s[i], i);
    printf("%d\n", ans);
    return 0;
}