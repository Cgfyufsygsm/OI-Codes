#include <cstdio>
#include <cctype>

const int maxn = 20000000 + 5;

int main() {
    int a, m, b = 0;
    scanf("%d %d", &a, &m);
    int phi = m, tmp = m;
    for (int i = 2; i * i <= tmp; ++i)
        if (tmp % i == 0) {
            phi = phi / i * (i - 1);
            while (tmp % i == 0) tmp /= i;
        }
    if (tmp > 1) phi = phi / tmp * (tmp - 1);
    int flag = 0;
    char c;
    while (!isdigit(c = getchar()));
    for (; isdigit(c); c = getchar()) {
        b = b * 10 + c - '0';
        if (b >= phi) flag = 1, b %= phi;
    }
    if (flag) b += phi;
    int ans = 1;
    for (; b; b >>= 1, a = 1ll * a * a % m)
        if (b & 1)
            ans = 1ll * ans * a % m;
    printf("%d\n", ans);
    return 0;
}