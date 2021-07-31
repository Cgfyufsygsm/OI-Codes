#include <cstdio>

long long p, q;

int main() {
    scanf("%lld %lld", &p, &q);
    printf("%lld\n", p == q ? p * p / 4 : (p - 1) * (q - 1) / 4);
    return 0;
}