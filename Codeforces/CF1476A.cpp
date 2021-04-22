#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

int n, k, kk;

inline int read()
{
    char c = getchar();
    int s = 0;
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

int main()
{
    int T = read();
    while (T--)
    {
        n = read(), k = kk = read();
        k *= (n / k) > 0 ? (n / k) : 1;
        while (n > k) k += kk;
        if (k % n == 0) printf("%d\n", k / n);
        else printf("%d\n", k / n + 1);
    }
    return 0;
}