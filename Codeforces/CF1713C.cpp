#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 1e5 + 5;
int a[maxn], sqr[maxn], tot, vis[maxn];

int main() {
    int T; cin >> T;
    for (int i = 0; i * i <= 3e5; ++i) sqr[tot = i] = i * i;
    while (T--) {
        int n; cin >> n;
        int cur = tot;
        DEC(i, n - 1, 0) {
            while (cur >= 0 && (sqr[cur] - i >= n || vis[sqr[cur] - i])) --cur;
            if (cur < 0) break;
            a[i] = sqr[cur] - i, vis[a[i]] = 1;
        }
        if (cur < 0) puts("-1");
        else FOR(i, 0, n - 1) cout << a[i] << " \n"[i == n - 1], vis[i] = 0;
    }
    return 0;
}