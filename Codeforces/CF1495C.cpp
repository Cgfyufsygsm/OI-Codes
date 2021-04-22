#include <cstdio>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 505;
char s[maxn][maxn];
int n, m;

int main()
{
    int T;
    scanf("%d", &T);
    while (T--)
    {
        scanf("%d %d", &n, &m);
        FOR(i, 1, n)
            scanf("%s", s[i] + 1);
        for (int j = 1 + (m % 3 == 0); j <= m;)
        {
            FOR(i, 1, n)
                s[i][j] = 'X';
            j += 3;
            if (j > m) break;
            int p = 2;
            if (n == 1 || (s[2][j - 1] != 'X' && s[2][j - 2] != 'X'))
                p = 1;
            s[p][j - 1] = s[p][j - 2] = 'X';
        }
        FOR(i, 1, n)
            puts(s[i] + 1);
    }
    return 0;
}