#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define szof(a) ((int) (a).size())

using namespace std;
using pii = pair<int, int>;
int n, m, ans;
vector<vector<int> > a, vis, val;
vector<pii> bad;
const int fx[] = {1, -1, 0, 0, 0};
const int fy[] = {0, 0, -1, 1, 0};

il bool bound(int x, int y) {
    return x <= n && y <= m && x >= 1 && y >= 1;
}

il bool check(int x, int y) {
    return a[x][y] == 1 ||
           (x + 1 <= n && a[x][y] > a[x + 1][y]) ||
           (x - 1 >= 1 && a[x][y] > a[x - 1][y]) ||
           (y + 1 <= m && a[x][y] > a[x][y + 1]) ||
           (y - 1 >= 1 && a[x][y] > a[x][y - 1]);
}

bool check(int x1, int y1, int x2, int y2) {
    swap(a[x1][y1], a[x2][y2]);
    int cnt = 0;
    FOR(k, 0, 4) {
        int x = x1 + fx[k], y = y1 + fy[k];
        if (!bound(x, y) || vis[x][y]) continue;
        vis[x][y] = 1, cnt += val[x][y] - (!check(x, y));
    }
    FOR(k, 0, 4) {
        int x = x2 + fx[k], y = y2 + fy[k];
        if (!bound(x, y) || vis[x][y]) continue;
        vis[x][y] = 1, cnt += val[x][y] - (!check(x, y));
    }
    FOR(k, 0, 4) {
        int x = x1 + fx[k], y = y1 + fy[k];
        if (bound(x, y)) vis[x][y] = 0;
        x = x2 + fx[k], y = y2 + fy[k];
        if (bound(x, y)) vis[x][y] = 0;
    }
    swap(a[x1][y1], a[x2][y2]);
    return cnt == bad.size();
}

unordered_set<long long> S;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    a.resize(n + 1), vis.resize(n + 1), val.resize(n + 1);
    FOR(i, 1, n) {
        a[i].resize(m + 1), vis[i].resize(m + 1), val[i].resize(m + 1);
        FOR(j, 1, m) cin >> a[i][j];
    }
    FOR(x, 1, n) FOR(y, 1, m) if (!check(x, y)) bad.push_back({x, y}), val[x][y] = 1;
    if (bad.size() > 10) return puts("2"), 0;
    else if (bad.empty()) return puts("0"), 0;
    FOR(k, 0, 4) {
        int x = bad[0].first + fx[k], y = bad[0].second + fy[k];
        if (!bound(x, y)) continue;
        FOR(i, 1, n) FOR(j, 1, m) {
            long long hsh1 = ((1ll * (x - 1) * m + y) * (n * m)) + ((i - 1) * m + j),
                    hsh2 = ((1ll * (i - 1) * m + j) * (n * m)) + ((x - 1) * m + y);
            if (!S.count(hsh1) && !S.count(hsh2)) ans += check(x, y, i, j), S.insert(hsh1), S.insert(hsh2);
        }
    }
    if (!ans) puts("2");
    else printf("1 %d\n", ans);
    return 0;
}