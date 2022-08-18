#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e5 + 5;
int a[maxn];

int main() {
    int T; cin >> T;
    while (T--) {
        int n; cin >> n;
        for (int i = n; i > 0; i -= 2) a[i - 1] = i, a[i] = i - 1;
        if (n & 1) a[1] = 1;
        FOR(i, 1, n) cout << a[i] << ' ';
        cout << '\n';
    }
    return 0;
}