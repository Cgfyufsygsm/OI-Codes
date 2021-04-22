#include <cstdio>
#include <cctype>
#include <algorithm>
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
        int a[105];
        int n = read();
        FOR(i, 1, n)
            a[i] = read();
        std::sort(a + 1, a + n + 1);
        int tot = 0;
        FOR(i, 1, n)
            if (a[i] == a[1]) ++tot;
            else break;
        printf("%d\n", n - tot);
    }
    return 0;
}