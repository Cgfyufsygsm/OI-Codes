#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define YES printf("YES\n")
#define NO printf("NO\n")

const int maxn = 1005;

char a[maxn][maxn], b[maxn][maxn];
int n;

void vxor(char (*m)[maxn], int j)
{
    FOR(i, 1, n)
        if (m[i][j] == '0')
            m[i][j] = '1';
        else m[i][j] = '0';
    return;
}

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d", &n);
        FOR(i, 1, n)
            scanf("%s", &a[i][1]);
        FOR(i, 1, n)
            scanf("%s", &b[i][1]);
        FOR(i, 1, n)
            FOR(j, 1, n)
                if (a[i][j] == b[i][j])
                    a[i][j] = '0';
                else a[i][j] = '1';
        FOR(j, 1, n)
            if (a[1][j] == '1')
                vxor(a, j);
        bool flag = 1;
        FOR(i, 1, n)
        {
            FOR(j, 2, n)
                if (a[i][j] != a[i][1])
                {
                    flag = 0;
                    break;
                }
            if (!flag) break;
        }
        if (flag) YES;
        else NO;
    }
    return 0;
}