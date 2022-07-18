#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;
const int maxn = 105;
int n, m, b[maxn][maxn], ans[maxn][maxn], vis[maxn][maxn], chose[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n >> m;
        using sb = pair<int, pair<int, int>>;
        priority_queue<sb, vector<sb>, greater<sb>> q;
        FOR(i, 1, n) FOR(j, 1, m) cin >> b[i][j], q.push({b[i][j], {i, j}}), vis[i][j] = 0;
        FOR(now, 1, m) {
            auto cur = q.top(); q.pop();
            int i = cur.second.first, j = cur.second.second;
            vis[i][j] = 1, ans[i][now] = b[i][j];
            chose[now] = i;
        }
        FOR(now, 1, m) {
            FOR(i, 1, n) if (chose[now] != i) FOR(j, 1, m) {
                if (!vis[i][j]) {
                    vis[i][j] = 1;
                    ans[i][now] = b[i][j];
                    break;
                }
            }
        }
        FOR(i, 1, n) {
            FOR(j, 1, m) cout << ans[i][j] << ' ';
            cout << '\n';
        }
    }
    return 0;
}