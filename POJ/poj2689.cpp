#include <cstdio>
#include <cmath>
#include <cstring>
#define int long long

int l, r;
const int maxr = 1ll << 31;
const int maxn = 1e6 +5;

int prime[50005], cntprime;
bool is_prime[maxn];

inline int max(int a, int b){return a > b ? a : b;}

signed main()
{
    is_prime[1] = 1;
    for (int i = 2; i <= 55000; ++i)
    {
        if (!is_prime[i])
            prime[++cntprime] = i;
        for (int j = 1; j <= cntprime &&  i * prime[j] <= 55000; ++j)
        {
            is_prime[i * prime[j]] = 1;
            if (!(i % prime[j]))
                break;
        }
    }
    while (scanf("%lld %lld", &l, &r) != EOF)
    {
        memset(is_prime, 0, sizeof is_prime);
        for (int i = 1; i <= cntprime && prime[i] * prime[i] <= r; ++i)
            for (int j = max(2, l / prime[i]); prime[i] * j <= r; ++j)
                if (prime[i] * j >= l)
                    is_prime[prime[i] * j - l] = 1;
        if (l == 1)
            is_prime[0] = 1;
        int mindist = maxr, maxdist = -maxr, last = -1, cnt = 0, c1, c2, d1, d2;
        for (int i = l; i <= r; ++i)
        {
            if (!is_prime[i - l])
            {
                ++cnt;
                if (last > 0)
                {
                    if (i - last > maxdist)
                        d1 = last, d2 = i, maxdist = i - last;
                    if (i - last < mindist)
                        c1 = last, c2 = i, mindist = i - last;
                }
                last = i;
            }
        }
        if (cnt < 2)
            printf("There are no adjacent primes.\n");
        else
            printf("%lld,%lld are closest, %lld,%lld are most distant.\n", c1, c2, d1, d2);
    }
    return 0;
}