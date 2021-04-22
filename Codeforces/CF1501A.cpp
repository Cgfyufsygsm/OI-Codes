#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int s = 0;
    char c = getchar();
    while (!isdigit(c))
        c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return s;
}

inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 105;
int a[maxn], b[maxn], tm[maxn], n;

int calc(int b, int a)
{
    int ret = b - a;
    return (ret & 1) ? ((b - a) >> 1) + 1 : ((b - a) >> 1);
}

int main()
{
    int T = read();
    while (T--)
    {
        n = read();
        FOR(i, 1, n)
            a[i] = read(), b[i] = read();
        FOR(i, 1, n) tm[i] = read();
        int now = 0;
        FOR(i, 1, n)
        {
            now += a[i] - b[i - 1] + tm[i];
            if (i == n) break;
            now = max(now, max(now + calc(b[i], a[i]), b[i]));
        }
        printf("%d\n", now);
    }
    return 0;
}