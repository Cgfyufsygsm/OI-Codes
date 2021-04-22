#include <cstdio>
#include <cctype>
#include <cstring>

const int maxn = 505;
int n, a[maxn], f[maxn][maxn];

inline int read()
{
    char c = getchar();
    int s = 0, x = 0;
    while (!isdigit(c))
    {
        if (c == '-')
            x = 1;
        c = getchar();
    }
    while (isdigit(c))
        s = 10 * s + c - '0', c = getchar();
    return x ? -s : s;
}

inline int min(int a, int b)
{
    return a < b ? a : b;
}

int main()
{
    n = read();
    memset(f, 0x3f, sizeof(f));
    for (int i = 1; i <= n; i++)
        a[i] = read(), f[i][i] = 1;
    for (int i = 1; i < n; i++)
        f[i][i + 1] = 1 + (a[i] != a[i + 1]);
    for (int l = 3; l <= n; l++)
        for (int i = 1, j = i + l - 1; j <= n; i++, j++)
        {
            if (a[i] == a[j])
                f[i][j] = f[i + 1][j - 1];
            for (int k = i; k < j; k++)
                f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
        }
    printf("%d\n", f[1][n]);
    return 0;
}
