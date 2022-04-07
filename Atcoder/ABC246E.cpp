#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
using namespace std;

const int maxn = 1505, fx[] = {1, 1, -1, -1}, fy[] = {1, -1, 1, -1};
queue<pair<int, int>> q;
char mp[maxn][maxn];
int n, sx, sy, tx, ty, f[maxn][maxn];

int main() {
    cin >> n >> sx >> sy >> tx >> ty;
    FOR(i, 1, n) cin >> &mp[i][1];
    f[sx][sy] = 1, q.push({sx, sy});
    auto check = [](int x, int y) {return x >= 1 && x <= n && y >= 1 && y <= n && mp[x][y] == '.';};
    while (!q.empty()) {
        auto now = q.front(); q.pop();
        FOR(k, 0, 3) {
            int x = now.first, y = now.second;
            while (true) {
                x += fx[k], y += fy[k];
                if (!check(x, y)) break;
                if (!f[x][y]) f[x][y] = f[now.first][now.second] + 1, q.push({x, y});
                else if (f[x][y] <= f[now.first][now.second]) break;
            }
        }
    }
    cout << f[tx][ty] - 1 << endl;
    return 0;
}