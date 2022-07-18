#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
const int maxn = 1e7 + 5, maxk = 19;
const int mod = 998244353, lcm = 720720;

int n, k, f[maxk][lcm + 5], ans, pown[maxk];
il void add(int &x, const int &y) {(x += y) >= mod ? x -= mod : (0-0);}

int main() {
    int a, x, y, M, sum = 0;
    cin >> n >> a >> x >> y >> k >> M;
    pown[0] = 1;
    FOR(i, 0, n - 1) {
        sum = (sum + (a / lcm) * lcm) % mod;
        ++f[1][a % lcm];
        a = (1ll * a * x + y) % M;
    }
    FOR(i, 1, k) pown[i] = 1ll * pown[i - 1] * n % mod;
    ans = 1ll * pown[k - 1] * k % mod * sum % mod;
    FOR(i, 1, k) {
        FOR(j, 0, lcm - 1) {
            add(f[i + 1][j], 1ll * (n - 1) * f[i][j] % mod);
            add(f[i + 1][j - j % i], f[i][j]);
            ans = (ans + 1ll * pown[k - i] * f[i][j] % mod * j % mod) % mod;
        }
    }
    cout << ans << endl;
    return 0;
}