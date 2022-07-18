#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int a, b; cin >> a >> b;
        int ans = 0, flg = 0;
        if (b == 1) ++b, flg = 1;
        int tmp = a;
        while (tmp) tmp /= b, ++ans;
        for (int i = 1, las = ans; ; ++i) {
            int tmpa = a, tmpb = b + i, cnt = i;
            while (tmpa) ++cnt, tmpa /= tmpb;
            if (cnt > las) break;
            ans = min(ans, cnt), las = cnt;
        }
        cout << ans + flg << endl;
    }
    return 0;
}