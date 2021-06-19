#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)

const int maxn = 105;

int f[maxn][maxn], n;
char s[maxn];
int nxt[maxn][maxn];

inline int min(int a, int b) {return a < b ? a : b;}

void KMP()
{
    memset(nxt, 0, sizeof nxt);
    FOR(k, 1, n)
    {
        nxt[k][k] = 0;
        for (int i = k + 1, j = 0; i <= n; ++i)
        {
            while (j && s[i] != s[k + j]) j = nxt[k][j];
            if (s[i] == s[k + j]) ++j;
            nxt[k][i] = j;
        }
    }
    return;
}

int main()
{
    while (scanf("%s", s + 1) && s[1] != '*')
    {
        memset(f, 0x3f, sizeof f);
        n = strlen(s + 1);
        FOR(i, 1, n) f[i][i] = 1;
        KMP();
        FOR(len, 2, n)
            for (int i = 1, j = i + len - 1; j <= n; ++i, ++j)
            {
                f[i][j] = len;
                int k = nxt[i][j];
                while (k)
                {
                    if (len % (len - k) == 0) f[i][j] = min(f[i][j], f[i][i + len - k - 1]);
                    k = nxt[i][k];
                }
                for (int k = i; k < j; ++k)
                    f[i][j] = min(f[i][j], f[i][k] + f[k + 1][j]);
            }
        printf("%d\n", f[1][n]);
    }
    return 0;
}