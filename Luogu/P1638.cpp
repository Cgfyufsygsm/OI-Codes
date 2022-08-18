#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 1e6 + 5;
int vis[maxn], a[maxn], n, m, cnt;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> m;
    FOR(i, 1, n) cin >> a[i];
    int l = 1, r = 1, minL = 1e9, ansl, ansr;
    vis[a[1]] = 1, cnt = 1;
    while (l <= r && r <= n) {
        if (cnt == m) {
            if (r - l + 1 < minL) {
                minL = r - l + 1;
                ansl = l, ansr = r;
            }
            if (l < r && !--vis[a[l++]]) --cnt;
        } else if (!vis[a[++r]]++) ++cnt;
    }
    cout << ansl << ' ' << ansr << endl;
    return 0;
}