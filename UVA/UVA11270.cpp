#include <cstdio>
#include <cstring>
#define p(i) (1 << (i - 1))

typedef long long ll;

ll f[2][(1 << 10) + 5];

int main()
{
    int n, m;
    while (~scanf("%d %d", &n, &m))
    {
        if (n < m) {int t = n; n = m; m = t;}
        int d = 0;
        memset(f, 0, sizeof f);
        f[0][(1 << m) - 1] = 1;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
            {
                d ^= 1;
                memset(f[d], 0, sizeof f[d]);
                for (int k = 0; k < (1 << m); ++k)
                {
                    if (k & p(j))
                        f[d][k ^ p(j)] += f[d ^ 1][k];
                    if ((j > 1) && !(k & p(j - 1)) && (k & p(j)))
                        f[d][k | p(j - 1)] += f[d ^ 1][k];
                    if ((i > 1) && !(k & p(j)))
                        f[d][k | p(j)] += f[d ^ 1][k];
                }
            }
        }
        printf("%lld\n", f[d][(1 << m) - 1]);
    }
    return 0;
}