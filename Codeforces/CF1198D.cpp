#include <cstdio>
#include <cstring>

inline int min(int a, int b) {return a < b ? a : b;}
inline int max(int a, int b) {return a > b ? a : b;}

const int maxn = 55;
char s[maxn][maxn];
int f[maxn][maxn][maxn][maxn];

int main()
{
    int n;
    scanf("%d", &n);
    for (int i = 1; i <= n; ++i)
    {
        scanf("%s", s[i] + 1);
        for (int j = 1; j <= n; ++j)
            f[i][j][i][j] = (s[i][j] == '#');
    }
    for (int xlen = 1; xlen <= n; ++xlen)
        for (int ylen = 1; ylen <= n; ++ylen)
        {
            if (xlen == 1 && ylen == 1)
                continue;
            for (int x1 = 1, x2 = x1 + xlen - 1; x2 <= n; ++x1, ++x2)
                for (int y1 = 1, y2 = y1 + ylen - 1; y2 <= n; ++y1, ++y2)
                {
                    f[x1][y1][x2][y2] = max(xlen, ylen);
                    for (int k = x1; k < x2; ++k)
                        f[x1][y1][x2][y2] = min(f[x1][y1][x2][y2], f[x1][y1][k][y2] + f[k + 1][y1][x2][y2]);
                    for (int k = y1; k < y2; ++k)
                        f[x1][y1][x2][y2] = min(f[x1][y1][x2][y2], f[x1][y1][x2][k] + f[x1][k + 1][x2][y2]);
                }
        }
    printf("%d\n", f[1][1][n][n]);
    return 0;
}