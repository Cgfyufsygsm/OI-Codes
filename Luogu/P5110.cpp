#include <cstdio>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

namespace Mker {
    unsigned long long SA, SB, SC;
    il void init() {scanf("%llu%llu%llu", &SA, &SB, &SC);}
    il unsigned long long rand() {
        SA ^= SA << 32, SA ^= SA >> 13, SA ^= SA << 1;
        unsigned long long t = SA;
        SA = SB, SB = SC, SC ^= t ^ SA; return SC;
    }
}

const int mod = 1e9 + 7, alpha = 233230706, x1 = 94153035, x2 = 905847205, maxn = 65536 + 5;
int f1[maxn], f2[maxn], f3[maxn], f4[maxn];

il int pow1(int n) {return 1ll * f2[n >> 16] * f1[n & 65535] % mod;}
il int pow2(int n) {return 1ll * f4[n >> 16] * f3[n & 65535] % mod;}

int main() {
    f1[0] = f3[0] = 1;
    FOR(i, 1, 65536) f1[i] = 1ll * f1[i - 1] * x1 % mod, f3[i] = 1ll * f3[i - 1] * x2 % mod;
    f2[0] = f4[0] = 1;
    FOR(i, 1, 65536) f2[i] = 1ll * f2[i - 1] * f1[65536] % mod, f4[i] = 1ll * f4[i - 1] * f3[65536] % mod;

    int T; scanf("%d", &T);
    Mker::init();

    int ans = 0;
    while (T--) {
        int n = Mker::rand() % (mod - 1);
        ans ^= 1ll * alpha * (pow1(n) - pow2(n) + mod) % mod;
    }
    printf("%d\n", ans);
}