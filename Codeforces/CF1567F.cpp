#include <cstdio>
#include <cstring>
#include <vector>
#include <utility>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

const int maxn = 505;
int a[maxn][maxn], num[maxn][maxn], n, m;
int ans[maxn][maxn], vis[maxn * maxn];

const int fx[] = {1, 0, 0, -1};
const int fy[] = {0, 1, -1, 0};

using std::pair;
using std::make_pair;
using std::vector;

pair<int, int> mun[maxn * maxn];
vector<int> G[maxn * maxn];

void dfs(int u, int col) {
    int x = mun[u].first, y = mun[u].second;
    ans[x][y] = col ? 4 : 1;
    vis[u] = 1;
    for (auto v : G[u]) if (!vis[v]) dfs(v, col ^ 1);
    return;
}

il void add(int u, int v) {
    G[u].push_back(v), G[v].push_back(u);
    return;
}

int main() {
    scanf("%d %d", &n, &m);
    int tot = 0;
    FOR(i, 1, n) {
        char s[maxn];
        scanf("%s", s + 1);
        FOR(j, 1, m) a[i][j] = (s[j] == 'X'), num[i][j] = ++tot, mun[tot] = make_pair(i, j);
    }
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            if (!a[i][j]) continue;
            int cnt = 0;
            FOR(k, 0, 3) {
                int tx = i + fx[k], ty = j + fy[k];
                if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
                if (!a[tx][ty]) ++cnt;
            }
            if (cnt == 1 || cnt == 3) return puts("NO"), 0;
            else if (cnt == 2) {
                int u = 0, v = 0;
                FOR(k, 0, 3) {
                    int tx = i + fx[k], ty = j + fy[k];
                    if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
                    if (!a[tx][ty] && !u) u = num[tx][ty];
                    else if (!a[tx][ty]) v = num[tx][ty];
                }
                add(u, v);
            } else if (cnt == 4) {
                add(num[i][j - 1], num[i + 1][j]);
                add(num[i][j + 1], num[i + 1][j]);
                add(num[i - 1][j], num[i][j + 1]);
                add(num[i - 1][j], num[i][j - 1]);
            }
        }
    }
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            if (a[i][j] || vis[num[i][j]]) continue;
            dfs(num[i][j], 0);
        }
    }
    puts("YES");
    FOR(i, 1, n) {
        FOR(j, 1, m) {
            if (a[i][j]) {
                FOR(k, 0, 3) {
                    int tx = i + fx[k], ty = j + fy[k];
                    if (tx < 1 || tx > n || ty < 1 || ty > m) continue;
                    if (!a[tx][ty]) ans[i][j] += ans[tx][ty];
                }
            }
            printf("%d ", ans[i][j]);
        }
        puts("");
    }
    return 0;
}