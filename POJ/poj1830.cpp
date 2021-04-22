#include <cstdio>
#include <cctype>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

inline int read()
{
    char c = getchar();
    int s = 0;
    bool x = 0;
    while (!isdigit(c))
        x = x | (c == '-'), c = getchar();
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

int n, a[100], ans;

int main()
{
    int K = read();
    while (K--)
    {
        n = read();
        FOR(i, 1, n)
            a[i] = read();
        FOR(i, 1, n)
        {
            a[i] ^= read();
            a[i] |= (1 << i);
        }
        for (int x = read(), y = read(); x && y; x = read(), y = read())
            a[y] |= (1 << x);
        ans = 1;
        FOR(i, 1, n)
        {
            FOR(j, i + 1, n)
                if (a[j] > a[i])
                    std::swap(a[i], a[j]);
            if (a[i] == 0)
            {
                ans = 1 << (n - i + 1);
                break;
            }
            if (a[i] == 1)
            {
                ans = 0;
                break;
            }
            DEC(k, n, 1)
            {
                if ((a[i] >> k) & 1)
                {
                    FOR(j, 1, n)
                        if (i != j && ((a[j] >> k) & 1))
                            a[j] ^= a[i];
                    break;
                }
            }
        }
        if (!ans)
            puts("Oh,it's impossible~!!");
        else printf("%d\n", ans);
    }
    return 0;
}