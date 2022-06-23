#include <bits/stdc++.h>
#include <fastio.hpp>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using YangTY::fastIO::is;
using YangTY::fastIO::os;
const int maxn = 2e3 + 5, maxs = (1 << 13), P[] = {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37, 41}, mod = 998244353;
int n, m, buc[maxn], pow2[maxn * maxn], f[maxs + 5], g[maxn][maxs + 5];

void init() {
    pow2[0] = 1;
    FOR(i, 1, n) pow2[i] = (pow2[i - 1] << 1) % mod;
    FOR(i, 1, 2000) {
        int tmp = i, msk = 0;
        if (!buc[i]) continue;
        FOR(j, 0, 12) while (tmp % P[j] == 0) tmp /= P[j], msk |= (1 << j);
        FOR(j, 0, maxs - 1) if ((j & msk) == msk) f[j] += buc[i];
        if (tmp == 43 * 43) tmp = 43;
        if (tmp > 1) FOR(j, 0, maxs - 1) if ((j & msk) == msk) g[tmp][j] += buc[i];
    }
    return;
}

il void add(int &a, int b) {a += b, a >= mod && (a -= mod);}
il void sub(int &a, int b) {a -= b, a < 0 && (a += mod);}

int p[18005], h[maxs + 5];

int main() {
    is >> n;
    FOR(i, 1, n) {
        int x; is >> x;
        ++buc[x];
    }
    init();
    is >> m;
    while (m--) {
        int c, msk = 0, ans = 0;
        is >> c, memcpy(h, f, sizeof h);
        FOR(j, 1, c) is >> p[j];
        sort(p + 1, p + c + 1), c = unique(p + 1, p + c + 1) - p - 1;
        FOR(i, 1, c) FOR(j, 0, 12) if (p[i] == P[j]) msk |= (1 << j);
        FOR(i, 1, c) if (p[i] > 41) FOR(j, 0, maxs - 1) h[j] -= g[p[i]][j];
        FOR(j, 0, maxs - 1) h[j] = pow2[h[j]];
        FOR(i, 1, c) if (p[i] > 41) FOR(j, 0, maxs - 1) h[j] = 1ll * h[j] * (pow2[g[p[i]][j]] - 1) % mod;
        for (int o = 2, k = 1; o <= maxs; o <<= 1, k <<= 1)
            for (int i = 0; i < maxs; i += o)
                for (int j = 0; j < k; ++j)
                    sub(h[i + j + k], h[i + j]);
        FOR(j, 0, maxs - 1) if ((msk & j) == msk) add(ans, h[j]);
        os << ans << '\n';
    }
    return 0;
}