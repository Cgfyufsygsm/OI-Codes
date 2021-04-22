#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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
        int n = read();
        if (n & 1)
        {
            FOR(i, 1, n)
            {
                int cnt = 0;
                FOR(j, i + 1, n)
                {
                    ++cnt;
                    if (cnt <= n / 2)
                        printf("1 ");
                    else printf("-1 ");
                }
            }
        }
        else
        {
            FOR(i, 1, n)
            {
                int cnt = 0;
                FOR(j, i + 1, n)
                {
                    ++cnt;
                    if (cnt <= (n - 1) / 2)
                        printf("1 ");
                    else if (cnt == n / 2)
                        printf("0 ");
                    else printf("-1 ");
                }
            }
        }
        printf("\n");
    }
    return 0;
}