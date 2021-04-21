#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 4e5 + 5, mod = 3;

char s[maxn];
int n, c[maxn];

int calc(char c)
{
    return c == 'B' ? 0 : (c == 'W' ? 1 : 2);
}

int C(int n, int m)
{
    if (m > n) return 0;
    int factn = 1;
    FOR(i, 1, n) factn *= i;
    FOR(i, 1, m) factn /= i;
    FOR(i, 1, n - m) factn /= i;
    return factn;
}

int lucas(int n, int m)
{
    if (m == 0) return 1;
    return C(n % mod, m % mod) * lucas(n / mod, m / mod) % mod;
}

int main()
{
    scanf("%d", &n);
    scanf("%s", s + 1);
    FOR(i, 1, n) c[i] = calc(s[i]);
    int ans = 0;
    FOR(i, 1, n)
        ans = (ans + c[i] * lucas(n - 1, i - 1)) % mod;
    if (n % 2 == 0) ans = (-ans + mod) % mod;
    printf("%c\n", ans == 0 ? 'B' : (ans == 1 ? 'W' : 'R'));
    return 0;
}