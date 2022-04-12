#include <bits/stdc++.h>
#include <atcoder/mincostflow>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 3e5 + 5;
using ll = long long;
const ll BIG = 1e12;
atcoder::mcf_graph<int, ll> G(305);

int s, t, n;

int main() {
    cin >> n; s = 301, t = 302;
    FOR(i, 1, 150) G.add_edge(s, i, 1, 0), G.add_edge(i + 150, t, 1, 0);
    FOR(i, 1, n) {
        int a, b, c;
        cin >> a >> b >> c;
        G.add_edge(a, b + 150, 1, BIG - c);
    }
    vector<ll> ans;
    for (int k = 1; k <= n; ++k) {
        auto g = G;
        auto p = g.flow(s, t, k);
        if (p.first < k) break;
        ans.push_back(BIG * k - p.second);
    }
    cout << ans.size() << endl;
    for (auto &x : ans) cout << x << endl;
    return 0;
}