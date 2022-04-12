#include <bits/stdc++.h>
#include <atcoder/modint>
#include <atcoder/convolution>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using mint = atcoder::modint998244353;
using atcoder::convolution;

const int maxn = 2e5 + 5;
vector<vector<mint>> P;
int cnt[maxn], n, k;

int main() {
    cin >> n >> k;
    FOR(i, 1, n) {
        int x; cin >> x;
        P.push_back({cnt[x]++, 1});
    }
    while (P.size() >= 2) {
        decltype(P) nxt;
        for (int i = 0; i < P.size() - 1; i += 2) nxt.push_back(convolution(P[i], P[i + 1]));
        if (P.size() & 1) nxt.push_back(P.back());
        nxt.swap(P);
    }
    auto &f = P.front();
    mint ans = 0;
    FOR(c, 0, (int)f.size() - 1) if (n - c <= k && ((n - c) & 1) == (k & 1)) ans += f[c];
    cout << ans.val() << endl;
    return 0;
}