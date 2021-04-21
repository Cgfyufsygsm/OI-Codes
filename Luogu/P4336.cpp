#include <cstdio>
#include <cctype>
#include <cstring>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 22, maxm = maxn * maxn / 2, mod = 1e9 + 7;
using std::swap;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

struct edge
{
    int u, v;
} e[maxn][maxm];

int n, m[maxn];
int size[1 << maxn];
int mat[maxn][maxn];

int det()
{
    int n = ::n - 1, ret = 1, rev = 1;
    FOR(i, 1, n)
        FOR(j, i + 1, n)
        {
            while (mat[i][i])
            {
                int div = mat[j][i] / mat[i][i];
                FOR(k, i, n)
                    mat[j][k] = (mat[j][k] - 1ll * div * mat[i][k] % mod + mod) % mod;
                swap(mat[i], mat[j]), rev = -rev;
            }
            swap(mat[i], mat[j]), rev = -rev;
        }
    FOR(i, 1, n)
        ret = 1ll * ret * mat[i][i] % mod;
    return (ret * rev + mod) % mod;
}

int main()
{
    n = read();
    FOR(i, 1, n - 1)
    {
        m[i] = read();
        FOR(j, 1, m[i])
            e[i][j].u = read(), e[i][j].v = read();
    }
    int up = (1 << (n - 1)) - 1, ans = 0;
    FOR(i, 1, up)
        size[i] = size[i >> 1] + (i & 1);
    FOR(set, 1, up)
    {
        memset(mat, 0, sizeof mat);
        for (int p = set, i = 1; p; p >>= 1, ++i)
        {
            if (!(p & 1)) continue;
            FOR(j, 1, m[i])
            {
                int u = e[i][j].u, v = e[i][j].v;
                ++mat[u][u], ++mat[v][v];
                mat[u][v] = (mat[u][v] - 1 + mod) % mod;
                mat[v][u] = (mat[v][u] - 1 + mod) % mod;
            }
        }
        ans = (ans + ((n - size[set]) % 2 ? det() : -det())) % mod;
    }
    printf("%d\n", (ans + mod) % mod);
    return 0;
}