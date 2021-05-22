#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5;

typedef long long ll;

ll read()
{
    ll s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

ll a, b, k, len;
ll binom[65][65];

void work(int a, int b, ll k)
{
    //printf("working %d %d %d\n", a, b, k);
    if (!a)
    {
        FOR(i, 1, b) putchar('b');
        return;
    }
    if (!b)
    {
        FOR(i, 1, a) putchar('a');
        return;
    }
    int len = a + b;
    ll sum = 0, last = 0;
    DEC(i, a, 0)
    {
        last = sum;
        sum += binom[len - i - 1][a - i];
        //printf("i = %d, sum = %d\n", i, sum);
        if (sum >= k)
        {
            FOR(j, 1, i) putchar('a');
            putchar('b');
            work(a - i, b - 1, k - last);
            return;
        }
    }
    return;
}

int main()
{
    a = read(), b = read(), k = read(), len = a + b;
    binom[0][0] = 1;
    FOR(i, 1, 60)
    {
        binom[i][0] = 1;
        FOR(j, 1, i)
            binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
    }
    work(a, b, k);
    return 0;
}