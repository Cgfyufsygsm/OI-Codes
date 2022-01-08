#include <bits/stdc++.h>

using namespace std;

int main() {
    ios::sync_with_stdio(false);
    int ans = 0, cnt = 0;
    int n; cin >> n;
    while (n--) {
        int x; cin >> x;
        if (x == ans) ++cnt;
        if (!cnt) ans = x, cnt = 1;
        if (x != ans) --cnt;
    }
    cout << ans << endl;
    return 0;
}