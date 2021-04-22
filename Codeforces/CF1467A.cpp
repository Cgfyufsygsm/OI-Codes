#include <cstdio>
#include <cctype>
#define R register
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

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
const int maxn = 2e5 + 5;

int main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        if (n == 1)
            printf("9");
        else
        {
            printf("98");
            FOR(i, 3, n)
                printf("%d", (i + 6) % 10);
        }
        printf("\n");
    }
    return 0;
}