#include <cstdio>
#include <cstring>

const int maxm = 25;
int n, m, mod, fail[maxm];
char s[maxm];

struct matrix
{
    int a[maxm][maxm];
    matrix()
    {
        memset(a, 0, sizeof a);
    }
    matrix operator*(matrix &b)
    {
        matrix ret;
        for (int i = 0; i < m; ++i)
            for (int j = 0; j < m; ++j)
                for (int k = 0; k < m; ++k)
                    ret.a[i][j] = (ret.a[i][j] + this->a[i][k] * b.a[k][j]) % mod;
        return ret;
    }
};

matrix pow(matrix a, int p)
{
    matrix ret;
    for (int i = 0; i <= m; ++i)
        ret.a[i][i] = 1;
    for (; p; p >>= 1)
    {
        if (p & 1)
            ret = ret * a;
        a = a * a;
    }
    return ret;
}

int main()
{
    scanf("%d %d %d", &n, &m, &mod);
    scanf("%s", s + 1);
    matrix f, g;
    f.a[0][0] = 1;
    for (int i = 2, j = 0; i <= m; ++i)
    {
        while (j && s[j + 1] != s[i])
            j = fail[j];
        if (s[j + 1] == s[i])
            ++j;
        fail[i] = j;
    }
    for (int i = 0; i < m; ++i)
    {
        for (int j = '0'; j <= '9'; ++j)
        {
            int p = i;
            while (p && s[p + 1] != j)
                p = fail[p];
            if (s[p + 1] == j) ++p;
            ++g.a[i][p];
        }
    }
    f = f * (g = pow(g, n));
    int ans = 0;
    for (int i = 0; i < m; ++i)
        (ans += f.a[0][i]) %= mod;
    printf("%d\n", ans);
    return 0;
}