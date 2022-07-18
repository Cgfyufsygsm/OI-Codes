#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const int maxn = 5005;
ll x[maxn], y[maxn];
int n, vis[maxn];

ll getDis(ll x1, ll y1, ll x2, ll y2) {return (x2 - x1) * (x2 - x1) + (y2 - y1) * (y2 - y1);}

int main() {
    cin >> n;
    FOR(i, 1, n) cin >> x[i] >> y[i];
    cout << (vis[1] = 1) << ' ';
    for (int c = 2, las = 1; c <= n; ++c) {
        ll nxtDis = 0; int nxt;
        FOR(i, 1, n) if (!vis[i] && getDis(x[las], y[las], x[i], y[i]) > nxtDis) nxt = i, nxtDis = getDis(x[las], y[las], x[i], y[i]);
        cout << (las = nxt) << ' ';
        vis[las] = 1;
    }
    return 0;
}