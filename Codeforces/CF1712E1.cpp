#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define szof(a) ((int) (a).size())

using namespace std;
using ll = long long;
const int maxn = 4e5 + 5, N = 4e5;
vector<int> fact[maxn];

ll binom(int n) {return (n - 2ll) * (n - 1ll) * n / 6;}

ll solve(int l, int r) { // count lcm(i, j, k) < i + j + k
    ll ret = 0;
    FOR(k, l + 2, r) {
        int cnt = 0;
        for (int x : fact[k]) if (x >= l && x < k) ++cnt;
        ret += cnt * (cnt - 1ll) / 2; // lcm = k
        if (k % 6 == 0 && k / 2 >= l) ++ret;
        if (k % 15 == 0 && k * 2 / 5 >= l) ++ret; // lcm = 2k
    }
    return ret;
}

int main() {
    FOR(i, 1, N) for (int j = i; j <= N; j += i) fact[j].emplace_back(i);
    int T; cin >> T;
    while (T--) {
        int l, r; cin >> l >> r;
        cout << binom(r - l + 1) - solve(l, r) << endl;
    }
    return 0;
}