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
        int n = read(), k = read();
        --k;
        if (n & 1)
        {
            k += k / (n >> 1);
            printf("%d\n", k % n + 1);
        }
        else printf("%d\n", k % n + 1);
    }
    return 0;
}