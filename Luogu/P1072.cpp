#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define R register
#define FOR(i, a, b) for (R int i = a; i <= b; ++i)

il int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

const int maxn = 1e5;
int prime[10005], cntp;
bool is_prime[2000000];

void make_prime()
{
    is_prime[0] = is_prime[1] = 1;
    FOR(i, 1, maxn)
    {
        if (!is_prime[i])
            prime[++cntp] = i;
        for (int j = 1; j <= cntp && i * prime[j] <= maxn; ++j)
        {
            is_prime[i * prime[j]] = 1;
            if (i % prime[j] == 0)
                break;
        }
    }
    return;
}

void calc(int &i, int *mi)
{
    FOR(idx, 1, cntp)
    {
        if (i < prime[idx])
            break;
        while (i % prime[idx] == 0)
            ++mi[idx], i /= prime[idx];
    }
    return;
}

int main()
{
    make_prime();
    int n = read();
    while (n--)
    {
        int a = read(), c = read(), b = read(), d = read();
        int ma[cntp], mb[cntp], mc[cntp], md[cntp], mx[cntp];
        memset(ma, 0, sizeof ma);
        memset(mb, 0, sizeof mb);
        memset(mc, 0, sizeof mc);
        memset(md, 0, sizeof md);
        bool flag;
        int d0 = d;
        calc(a, ma), calc(b, mb), calc(c, mc), calc(d, md);
        int ans = 1;
        FOR(i, 1, cntp)
        {
            if (prime[i] > d0)
                break;
            mx[i] = 0;
            if (ma[i] > mc[i] && mb[i] < md[i] && mc[i] == md[i])
                mx[i] = 1;
            else if (ma[i] > mc[i] && mb[i] == md[i] && mc[i] <= md[i])
                mx[i] = 1;
            else if (ma[i] == mc[i] && mb[i] < md[i] && mc[i] <= md[i])
                mx[i] = 1;
            else if (ma[i] == mc[i] && mb[i] == md[i] && mc[i] <= md[i])
                mx[i] = md[i] - mc[i] + 1;
            if (d0 % prime[i] == 0)
                ans *= mx[i];
        }
        if (!(a == 1 && b == 1 && c == 1 && d == 1))
            if (a < c || b > d)
                ans = 0;
            if ((a == c && c != 1) || (b == d && d != 1))
                ans <<= 1;
        printf("%d\n", ans);
    }
    return 0;
}