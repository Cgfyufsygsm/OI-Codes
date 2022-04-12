#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

int n, k, a[22], p[22], cnt;

void insert(int x0) {
    int x = x0;
    DEC(j, n - 1, 0) if ((x >> j) & 1) {
        if (!p[j]) {
            p[j] = x, a[cnt++] = x0;
            break;
        } else x ^= p[j];
    }
    return;
}

int main() {
    cin >> n >> k;
    FOR(i, 0, (1 << n) - 1) if (__builtin_popcount(i) == k) insert(i);
    if (cnt < n) return puts("0"), 0;
    cout << 1 << endl;
    FOR(i, 0, (1 << n) - 1) {
        int g = i ^ (i >> 1), now = 0;
        FOR(j, 0, n - 1) if ((g >> j) & 1) now ^= a[j];
        cout << now << ' ';
    }
    return 0;
}