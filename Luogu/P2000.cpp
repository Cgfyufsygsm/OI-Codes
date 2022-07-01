#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using ll = long long;
using namespace std;
const int mod = 998244353, maxn = 4e6 + 5;

int qPow(int base, int exp = mod - 2) {
    int ret = 1;
    for (base %= mod; exp; exp >>= 1, base = 1ll * base * base % mod)
        if (exp & 1) ret = 1ll * ret * base % mod;
    return ret;
}

const int G = 3, invG = qPow(3);
int tr[maxn], invN, n = 1, len;
ll f[maxn], g[maxn], g0[maxn], w[maxn];
char s[maxn];

void NTT(ll *f, int rev) {
    FOR(i, 0, n - 1) if (i < tr[i]) swap(f[i], f[tr[i]]);
    w[0] = 1;
    for (int l = 1; l < n; l <<= 1) {
        int tG = qPow(rev ? G : invG, (mod - 1) / (l << 1));
        FOR(i, 1, l - 1) w[i] = 1ll * w[i - 1] * tG % mod;
        for (int k = 0; k < n; k += (l << 1))
            for (int p = 0; p < l; ++p) {
                int tt = 1ll * w[p] * f[k + l + p] % mod;
                f[k + l + p] = (f[k + p] - tt + mod) % mod;
                f[k + p] = (f[k + p] + tt) % mod;
            }
    }
    if (!rev) FOR(i, 0, n - 1) f[i] = 1ll * invN * f[i] % mod;
    return;
}

void work(int x) {
    FOR(i, 0, n - 1) g[i] = g0[i];
    g[0] += x;
    NTT(f, 1), NTT(g, 1);
    FOR(i, 0, n - 1) f[i] = 1ll * f[i] * g[i] % mod, g[i] = 0;
    NTT(f, 0);
    FOR(i, 0, n - 1) f[i + 1] = f[i + 1] + f[i] / 10,f[i] %= 10;
    return;
}

int main() {
    scanf("%s", s), len = strlen(s);
    FOR(i, 0, len - 1) g0[i] = s[len - i - 1] - '0';
    while (n <= 5 * len) n <<= 1;
    FOR(i, 0, n - 1) tr[i] = (tr[i >> 1] >> 1) | ((i & 1) ? (n >> 1) : 0);
    invN = qPow(n);
    f[0] = 1;
    FOR(i, 0, len - 1) f[i] += g0[i];
    work(2), work(3), work(4);
    DEC(i, n - 1, 0) f[i - 1] += (f[i] % 24) * 10, f[i] /= 24;
    bool flg = 0;
    DEC(i, n - 1, 0) if (flg || f[i]) flg = 1, printf("%lld", f[i]);
    return 0;
}