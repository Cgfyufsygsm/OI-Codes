#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

const int LG = 30;
int p[LG + 5], a[105], n;

bool insert(int x) {
    DEC(j, LG, 0) if ((x >> j) & 1) {
        if (!p[j]) {
            p[j] = x;
            break;
        } else x ^= p[j];
    }
    return x;
}

int main() {
    cin >> n;
    FOR(i, 1, n) cin >> a[i];
    sort(a + 1, a + n + 1, greater<int>());
    long long ans = 0;
    FOR(i, 1, n) if (!insert(a[i])) ans += a[i];
    cout << ans << endl;
}