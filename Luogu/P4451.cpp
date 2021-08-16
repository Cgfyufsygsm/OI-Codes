#include <cstdio>

const int mod = 1e9 + 7, sqrt2 = 59713600;

int qPow(int a, int b = mod - 2, int p = mod) {
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % p)
        if (b & 1) ret = 1ll * ret * a % p;
    return ret;
}

char str[10005];

int main() {
    scanf("%s", str + 1);
    int n = 0;
    for (int i = 1; str[i]; ++i)
        n = (10ll * n + str[i] - '0') % (mod - 1);
    printf("%d\n", 1ll * sqrt2 * qPow(4) % mod * (qPow(1 + sqrt2, n) - qPow(1 - sqrt2 + mod, n) + mod) % mod);
    return 0;
}