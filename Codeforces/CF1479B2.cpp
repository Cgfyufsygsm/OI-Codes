#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
const int maxn = 1e5 + 5;
int n, a[maxn], nxt[maxn], pos[maxn];

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n) cin >> a[i], pos[i] = n + 1;
    DEC(i, n, 1) nxt[i] = pos[a[i]], pos[a[i]] = i;
    nxt[0] = n + 1;
    int t1 = 0, t2 = 0, ans = 0;
    FOR(i, 1, n) {
        if (a[i] != a[t1] && a[i] != a[t2]) {
            ++ans;
            if (nxt[t1] > nxt[t2]) t1 = i;
            else t2 = i;
        } else if (a[i] == a[t1]) t1 = i;
        else if (a[i] == a[t2]) t2 = i;
        else t1 = t2 = i;
    }
    cout << ans << endl;
    return 0;
}