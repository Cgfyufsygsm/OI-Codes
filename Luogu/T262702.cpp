#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define szof(a) ((int) (a).size())
#define debug(...) fprintf(stderr, __VA_ARGS__)
#define fileIn(s) freopen(s, "r", stdin)
#define fileOut(s) freopen(s, "w", stdout)
#define clr(f, n) memset(f, 0, (sizeof(int)) * (n))
#define cpy(f, g, n) memcpy(f, g, (sizeof(int)) * (n))
#define lowbit(x) (x & -x)

using namespace std;

const int maxn = 1e5 + 5, mod = 1e9 + 7;
int n, m;
vector<int> Px[maxn], Py[maxn];
vector<pair<int, int>> op[maxn];
int t[maxn];

void add(int x, int v) { for (; x <= n; x += lowbit(x)) t[x] += v; }
int query(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x)) ret += t[x];
    return ret;
}
il int query(int x, int y) {return query(y) - query(x - 1);}

int main() {
    scanf("%d %d", &n, &m);
    FOR(i, 1, m) {
        int x, y; scanf("%d %d", &x, &y);
        Px[x].emplace_back(y), Py[y].emplace_back(x);
    }
    FOR(i, 1, n) {
        sort(Px[i].begin(), Px[i].end());
        sort(Py[i].begin(), Py[i].end());
        for (int j = 1; j < szof(Py[i]); ++j)
            if (Py[i][j - 1] + 1 < Py[i][j]) op[Py[i][j - 1] + 1].emplace_back(i, 1), op[Py[i][j]].emplace_back(i, -1);
    }
    int ans = 0;
    FOR(i, 1, n) {
        for (auto &p : op[i]) add(p.first, p.second);
        for (int j = 1; j < szof(Px[i]); ++j)
            if (Px[i][j - 1] + 1 < Px[i][j])
                ans = (ans + query(Px[i][j - 1] + 1, Px[i][j] - 1)) % mod;
    }
    printf("%d\n", ans);
    return 0;
}