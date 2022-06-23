#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 55;
int a[maxn], n;

int main() {
    int T; cin >> T;
    while (T--) {
        cin >> n;
        FOR(i, 1, n) cin >> a[i];
        if (n & 1) cout << "Mike" << endl;
        else {
            int minv = 2e9, pos;
            FOR(i, 1, n) if (a[i] < minv) pos = i, minv = a[i];
            if (pos & 1) cout << "Joe" << endl;
            else cout << "Mike" << endl;
        }
    }
    return 0;
}