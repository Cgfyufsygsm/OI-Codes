#include <cstdio>

const int mod = 10007;

int qPow(int base, int exp) {
    int ret = 1;
    for (base %= mod; exp; exp >>= 1, base = 1ll * base * base % mod)
        if (exp & 1) ret = 1ll * ret * base % mod;
    return ret;
}

const int inv4 = qPow(4, mod - 2);

int main() {
    int T; scanf("%d", &T);
    while (T--) {
        int n;
        scanf("%d", &n);
        printf("%d\n", 1ll * inv4 * (qPow(4, n) + qPow(2, n + 1)) % mod);
    }
    return 0;
}