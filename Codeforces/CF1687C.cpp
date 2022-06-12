#include <bits/stdc++.h>
#include <fastio.hpp>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using YangTY::fastIO::is;
using YangTY::fastIO::os;
using ll = long long;
const int maxn = 2e5 + 5;
int n, m, deg[maxn];
ll a[maxn], b[maxn];
vector<int> G[maxn];
pair<int, int> e[maxn];

int main() {
    int T; is >> T;
    while (T--) {
        is >> n >> m;
        FOR(i, 1, n) is >> a[i];
        FOR(i, 1, n) is >> b[i], a[i] -= b[i], a[i] += a[i - 1];
        set<int> S;
        FOR(i, 0, n) S.insert(i), vector<int>().swap(G[i]);
        FOR(i, 1, m) {
            int &l = e[i].first, &r = e[i].second;
            is >> l >> r;
            G[l - 1].push_back(i), G[r].push_back(i);
            deg[i] = 2;
        }
        queue<int> q;
        FOR(i, 0, n) if (!a[i]) q.push(i), S.erase(i);
        while (!q.empty()) {
            int x = q.front(); q.pop();
            for (int id : G[x]) if (!--deg[id]) {
                int l = e[id].first, r = e[id].second;
                auto lt = S.lower_bound(l), rt = S.upper_bound(r);
                for (auto it = lt; it != rt; ++it) q.push(*it);
                S.erase(lt, rt);
            }
        }
        os << (S.empty() ? "YES" : "NO") << '\n';
    }
    return 0;
}