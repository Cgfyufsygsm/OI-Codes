#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 2e5 + 5;
int buc[maxn], n, rt;

int main() {
    ios::sync_with_stdio(false);
    cin >> n >> rt;
    int cnt = 1, ans = 0;
    FOR(i, 1, n) {
        int x; cin >> x;
        if (i == rt && x) ++ans;
        else ++buc[x];
    }
    for (int i = 1; cnt < n; ++i) {
        if (buc[i]) cnt += buc[i];
        else ++cnt;
        ans += !buc[i];
    }
    cout << ans << endl;
    return 0;
}