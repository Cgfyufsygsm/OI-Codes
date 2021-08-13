#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1 << 21;
    char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
    il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
    template<typename T> void read(T &n) {
        int x = 0; n = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            n = n * 10 + c - '0', c = getchar();
        n = x ? -n : n;
    }
}

using namespace fastIO;

typedef long long ll;
const int mod = 1e9 + 7;

ll qPow(ll a, ll b, ll p = mod) {
    if (b < 0) b += mod - 1;
    ll ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % p)
        if (b & 1) ret = 1ll * ret * a % mod;
    return ret;
}

il int inv(int a, int m = mod) {return qPow(a, m - 2, m);}

const int maxw = 1005;
int m, w;
ll p[maxw], a[maxw];
ll mat[105][105], f[105], sum[105];

void initMat() {
    FOR(i, 1, m + 2) {
        sum[i] = (qPow(i, m) + sum[i - 1]) % mod;
        mat[i - 1][0] = 1, mat[i - 1][m + 2] = sum[i];
        FOR(j, 1, m + 1)
            mat[i - 1][j] = mat[i - 1][j - 1] * i % mod;
    }
    return;
}

//行：[0, m + 1]，列：[0, m + 2]

void gauss() {
    FOR(i, 0, m + 1) {
        int r = i;
        FOR(j, i + 1, m + 1)
            if (mat[j][i] > mat[r][i])
                r = j;
        std::swap(mat[r], mat[i]);
        ll div = inv(mat[i][i]);
        FOR(j, i, m + 2) mat[i][j] = mat[i][j] * div % mod;
        FOR(j, i + 1, m + 1) {
            div = mat[j][i];
            FOR(k, i, m + 2)
                mat[j][k] = ((mat[j][k] - mat[i][k] * div % mod) % mod + mod) % mod;
        }
    }
    f[m + 1] = mat[m + 1][m + 2];
    DEC(i, m, 0) {
        f[i] = mat[i][m + 2];
        FOR(j, i + 1, m + 1)
            f[i] = ((f[i] - mat[i][j] * f[j] % mod) % mod + mod) % mod;
    }
    return;
}

int main() {
    read(m), read(w);
    FOR(i, 1, w) read(p[i]), read(a[i]);
    initMat();
    gauss();
    ll ans = 0;
    FOR(i, 0, m + 1) {
        ll tmp = 1;
        FOR(j, 1, w)
            tmp = qPow(p[j], a[j] * i % (mod - 1)) * (1ll - qPow(p[j], m - i) + mod) % mod * tmp % mod;
        ans = (ans + tmp * f[i] % mod) % mod;
    }
    printf("%lld\n", ans);
    return 0;
}