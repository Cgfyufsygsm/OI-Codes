#include <bits/stdc++.h>

using namespace std;

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        if (n % 7 == 0) cout << n << endl;
        else {
            n -= (n % 10);
            for (int i = 0; i < 10; ++i) if ((n + i) % 7 == 0) {
                cout << n + i << endl;
                break;
            }
        }
    }
    return 0;
}