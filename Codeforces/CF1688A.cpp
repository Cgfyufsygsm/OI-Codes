#include <bits/stdc++.h>

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        int ans = (n & -n);
        if (!(ans ^ n)) {
            if (n == 1) ans |= 2;
            else ans |= 1;
        }
        cout << ans << endl;
    }
    return 0;
}