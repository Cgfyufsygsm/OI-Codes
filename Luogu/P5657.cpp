#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef unsigned long long ull;

ull tmp[65];

void work(ull n, ull k)
{
    if (n == 1) return (void)printf("%d", k);
    if (k >= (1llu << (n - 1)))
        printf("1"), work(n - 1, tmp[n] - k);
    else printf("0"), work(n - 1, k);
    return;
}

int main()
{
    FOR(i, 1, 63) tmp[i] = (1llu << i) - 1;
    tmp[64] = (ull)(-1);
    ull n, k;
    scanf("%llu %llu", &n, &k);
    work(n, k);
    return 0;
}