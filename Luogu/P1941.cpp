#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define a(x) game[x]
using namespace std;

const int maxn = 10005, INF = 0x3f3f3f3f;
int n, m, k;
int f[maxn][3005];

struct node
{
    int x, y, high, low;
    bool flag;
} game[maxn];

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
    n = read(), m = read(), k = read();
    for (int i = 1; i <= n; i++)
    {
        a(i).x = read(), a(i).y = read();
        a(i).high = m, a(i).low = 1;
    }
    int p, l, h;
    for (int i = 1; i <= k; i++)
    {
        p = read(), l = read(), h = read();
        a(p).flag = 1,
        a(p).high = h - 1,
        a(p).low = l + 1;
    }
    memset(f, INF, sizeof(f));
    for (int i = 1; i <= m; i++)
        f[0][i] = 0;
    for (int i = 1; i <= n; i++)
    {
        for (int j = a(i).x + 1; j <= m + a(i).x; j++)
            f[i][j] = min(f[i][j], min(f[i][j - a(i).x] + 1, f[i - 1][j - a(i).x] + 1));
        for (int j = m; j <= m + a(i).x; j++)
            f[i][m] = min(f[i][m], f[i][j]);
        for (int j = 1; j <= m - a(i).y; j++)
            f[i][j] = min(f[i][j], f[i - 1][j + a(i).y]);
        for (int j = 1; j < a(i).low; j++)
            f[i][j] = INF;
        for (int j = m; j > a(i).high; j--)
            f[i][j] = INF;
    }
    int ans = INF;
    for (int i = 1; i <= m; i++)
        ans = min(ans, f[n][i]);
    if (ans < INF)
    {
        printf("1\n%d\n", ans);
        return 0;
    }
    for (int i = n - 1; i >= 1; i--)
        for (int j = 1; j <= m; j++)
            if (f[i][j] < INF)
            {
                ans = 0;
                for (int t = 1; t <= i; t++)
                    if (a(t).flag)
                        ans++;
                printf("0\n%d\n", ans);
                return 0;
            }
}