#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 22, maxs = 1 << 21 | 50;

struct String {
    int minp, sum;
    map<int, int> H;
    vector<int> L;
    int delta;
    void init(string s) {
        int p = 0;
        minp = 1e9;
        map<int, bool> no;
        FOR(i, 0, (int)s.size() - 1) {
            if (s[i] == '(') ++p;
            else --p;
            if (s[i] == ')') {
                if (!no[p]) ++H[p];
            } else no[p] = 1;
            minp = min(minp, p);
        }
        sum = p;
        if (H.empty()) return;
        delta = H.begin()->first;
        int R = H.rbegin()->first;
        L.resize(R - delta + 1);
        for (auto p : H) L[p.first - delta] = p.second;
        return;
    }
    il int query(int x) {
        x -= delta;
        if (x < 0 || x >= (int)L.size()) return 0;
        return L[x];
    }
} s[22];

int dp[maxs], sum[maxs], n;

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> n;
    FOR(i, 1, n) {
        string str; cin >> str;
        s[i].init(str);
    }
    FOR(S, 0, (1 << n) - 1) FOR(i, 1, n) if ((1 << (i - 1)) & S) sum[S] += s[i].sum;
    memset(dp, -1, sizeof dp);
    dp[0] = 0;
    int ans = 0;
    FOR(S, 1, (1 << n) - 1) {
        FOR(i, 1, n) if (S & (1 << (i - 1))) {
            int F = S ^ (1 << (i - 1));
            if (dp[F] == -1) continue;
            int nows = sum[F], cur = dp[F] + s[i].query(-nows);
            ans = max(ans, cur);
            if (nows + s[i].minp < 0) continue;
            dp[S] = max(dp[S], cur);
        }
    }
    cout << ans << '\n';
    return 0;
}