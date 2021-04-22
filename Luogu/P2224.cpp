#include <cstdio>
#include <cctype>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

int read()
{
    int ret = 0; int rev = 0;
    char c = getchar();
    while (!isdigit(c))
        rev |= (c == '-'), c = getchar();
    while (isdigit(c))
        ret = 10 * ret + c - '0', c = getchar();
    return rev ? -ret : ret;
}

inline int min(int a, int b) {return a < b ? a : b;}
inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 6000 + 5;

int f[maxn * 5];

int main()
{
    int n = read(), up, down, tmp, ans = 0x7fffffff;
    FOR(i, 1, n)
    {
        int a = read(), b = read(), c = read();
        up += max(max(a, b), c), tmp = down;
        down = 0x7fffffff;
        DEC(j, up, tmp)
        {
            int t = 0x3fffffff;
            if (a && j - a >= tmp) t = min(t, f[j - a]);
            if (b) t = min(t, f[j] + b);
            if (c && j - c >= tmp) t = min(t, f[j - c] + c);
            if (t < 0x3fffffff)
                down = min(down, j);
            f[j] = t;
        }
    }
    FOR(i, down, up)
        ans = min(ans, max(i, f[i]));
    printf("%d\n", ans);
    return 0;
}