#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define YES printf("YES\n")
#define NO printf("NO\n")

const int maxn = 1005;

char g[maxn][maxn];
int n, m;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &m);
        FOR(i, 1, n)
            scanf("%s", &g[i][1]);
        int flag = 0;
        if (m & 1)
        {
            YES;
            FOR(i, 1, m + 1)
                printf("%d ", (i & 1) ? 1 : 2);
        }
        else if (n == 2)
        {
            if (g[1][2] != g[2][1]) NO;
            else
            {
                YES;
                FOR(i, 1, m + 1) printf("%d ", (i & 1) ? 1 : 2);
            }
        }
        else
        {
            YES;
            int x = 0, y, z;
            if (g[1][2] == g[2][1]) x = 1, y = 2;
            else if (g[2][3] == g[3][2]) x = 2, y = 3;
            else if (g[3][1] == g[1][3]) x = 1, y = 3;
            if (x)
                FOR(i, 1, m + 1) printf("%d ", (i & 1) ? x : y);
            else
            {
                if (g[1][2] == g[2][3]) x = 1, y = 2, z = 3;
                else if (g[2][3] == g[3][1]) x = 2, y = 3, z = 1;
                else if (g[3][1] == g[1][2]) x = 3, y = 1, z = 2;
                if ((m >> 1) & 1)
                    FOR(i, 1, m + 1)
                        if (i % 4 == 1) printf("%d ", x);
                        else if (i % 2 == 0) printf("%d ", y);
                        else printf("%d ", z);
                else
                    FOR(i, 1, m + 1)
                        if (i & 1) printf("%d ", y);
                        else if (i % 4 == 2) printf("%d ", z);
                        else printf("%d ", x);
            }
        }
        puts("");
    }
    return 0;
}