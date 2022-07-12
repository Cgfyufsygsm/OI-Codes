#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

const int maxn = 35, mod = 998244353, maxv = 152501;
int n, m, G[maxn][maxn];
int cntW[maxv + 5], maxw;

int qPow(int a, int b) {
    int ret = 1;
    for (a %= mod; b; b >>= 1, a = 1ll * a * a % mod)
        if (b & 1) ret = 1ll * ret * a % mod;
    return ret;
}

using pii = pair<int, int>;

pair<int, int> a[maxn][maxn];

il pii operator+(const pii &a, const pii &b) {
    return {(a.first + b.first) % mod, (a.second + b.second) % mod};
}
il pii operator-(const pii &a, const pii &b) {
    return {(a.first - b.first + mod) % mod, (a.second - b.second + mod) % mod};
}
il pii operator*(const pii &a, const pii &b) {
    return {1ll * a.first * b.first % mod, (1ll * a.first * b.second % mod + 1ll * a.second * b.first % mod) % mod};
}
il pii operator/(const pii &a, const pii &b) {
    int inv = qPow(b.first, mod - 2);
    auto bb = (pii){inv, (mod - 1ll) * inv % mod * inv % mod * b.second % mod};
    return a * bb;
}

void buildMat(int d) {
    memset(a, 0, sizeof a);
    FOR(i, 1, n) FOR(j, 1, n) if (j != i && G[i][j] && G[i][j] % d == 0) a[i][i] = a[i][i] + (pii){1, G[i][j]};
    FOR(i, 1, n) FOR(j, 1, n) if (j != i && G[i][j] && G[i][j] % d == 0) a[i][j] = a[i][j] - (pii){1, G[i][j]};
    return;
}

int getPhi(int n) {
    int ans = n;
    for (int i = 2; i * i <= n; ++i) if (n % i == 0) {
        ans = ans / i * (i - 1);
        while (n % i == 0) n /= i;
    }
    if (n > 1) ans = ans / n * (n - 1);
    return ans;
}

int solve() {
    int n = ::n - 1;
    pii ans = pii(1, 0);
    int rev = 0;
    FOR(i, 1, n) {
        if (!a[i][i].first) FOR(j, i + 1, n) {
            if (a[j][i].first) {
                rev ^= 1;
                swap(a[i], a[j]);
                break;
            }
        }
        auto inv = pii(1, 0) / a[i][i];
        FOR(j, i + 1, n) {
            auto div = a[j][i] * inv;
            FOR(k, i, n) a[j][k] = a[j][k] - div * a[i][k];
        }
        ans = ans * a[i][i];
    }
    return (rev ? (pii(0, 0) - ans) : ans).second;
}

int main() {
    cin >> n >> m;
    FOR(i, 1, m) {
        int u, v, w; cin >> u >> v >> w;
        G[u][v] = G[v][u] = w;
        for (int j = 1; j * j <= w; ++j) if (w % j == 0) {
            ++cntW[j];
            if (j * j != w) ++cntW[w / j];
        }
        maxw = max(maxw, w);
    }
    int ans = 0;
    FOR(d, 1, maxw) {
        if (cntW[d] < n - 1) continue;
        buildMat(d);
        ans = (ans + 1ll * getPhi(d) * solve() % mod) % mod;
    }
    cout << ans << endl;
    return 0;
}