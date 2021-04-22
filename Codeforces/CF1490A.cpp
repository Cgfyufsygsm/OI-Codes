#include <cstdio>
#include <cctype>
#include <cmath>
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
inline int max(int a, int b) {return a > b ? a : b;}

int main()
{
    int T = read();
    while (T--)
    {
        double a[105];
        int n = read();
        FOR(i, 1, n)
            a[i] = read();
        int ans = 0;
        FOR(i, 1, n - 1)
        {
            int x = max(a[i], a[i + 1]), y = min(a[i], a[i + 1]);
            if (x <= (y << 1)) continue;
            ans += floor(log2((x - 0.1) / y));
        }
        printf("%d\n", ans);
    }
    return 0;
}