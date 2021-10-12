#include <cstdio>

int qPow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % p)
        if (b & 1) ret = 1ll * a * ret % p;
    return ret;
}

int main() {
    int n, m, k, x;
    scanf("%d %d %d %d", &n, &m, &k, &x);
    printf("%lld\n", (1ll * m * qPow(10, k, n) % n + x) % n);
    return 0;
}