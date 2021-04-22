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

inline int min(int a, int b) {return a < b ? a : b;}

int c[3];

int main()
{
    int T = read();
    while (T--)
    {
        int n = read();
        c[0] = c[1] = c[2] = 0;
        FOR(i, 1, n)
            ++c[read() % 3];
        int ans = 0;
        while (min(c[0], min(c[1], c[2])) != n / 3)
        {
            FOR(i, 0, 2)
            {
                if (c[i] > n / 3)
                {
                    ++ans;
                    --c[i], ++c[(i + 1) % 3];
                }
            }
        }
        printf("%d\n", ans);
    }
    return 0;
}