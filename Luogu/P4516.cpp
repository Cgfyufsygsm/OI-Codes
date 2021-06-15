#include <cstdio>
#include <cctype>
#include <vector>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

typedef long long ll;
const int maxn = 1e5 + 5, maxk = 101;
const ll mod = 1e9 + 7;

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

il int min(int a, int b) {return a < b ? a : b;}

std::vector<int> edge[maxn];

il void add(int u, int v)
{
    edge[u].push_back(v);
    edge[v].push_back(u);
    return;
}

#define GO(u) for (unsigned e = 0, v = edge[u][e]; e < edge[u].size(); ++e, v = edge[u][e])

int n, k;
int f[maxn][maxk][2][2], size[maxn];
//f[u][j][0/1][0/1]：u 子树，装了 j 个监听器，u点有没有装，u点有没有被控制

void add(int &x, ll y)
{
    if (y >= mod) y %= mod;
    for (x += y; x >= mod; x -= mod);
    return;
}

int tmp[maxk][2][2];

void dfs(int u, int fa)
{
    size[u] = f[u][0][0][0] = f[u][1][1][0] = 1;
    GO(u)
    {
        if (v == fa) continue;
        dfs(v, u);
        FOR(i, 0, min(k, size[u]))
            FOR(j, 0, 1)
                FOR(k, 0, 1)
                    tmp[i][j][k] = f[u][i][j][k], f[u][i][j][k] = 0;
        FOR(i, 0, min(k, size[u]))
            FOR(j, 0, min(k - i, size[v]))
            {
                add(f[u][i + j][0][0], 1ll * tmp[i][0][0] * f[v][j][0][1]);

                add(f[u][i + j][0][1], 1ll * tmp[i][0][0] * f[v][j][1][1] + 1ll * tmp[i][0][1] * (f[v][j][1][1] + f[v][j][0][1]));

                add(f[u][i + j][1][0], 1ll * tmp[i][1][0] * (f[v][j][0][1] + f[v][j][0][0]));

                add(f[u][i + j][1][1], 1ll * tmp[i][1][0] * (f[v][j][1][0] + f[v][j][1][1]));
                add(f[u][i + j][1][1], 1ll * tmp[i][1][1] * ((ll)f[v][j][0][0] + (ll)f[v][j][1][0] + (ll)f[v][j][0][1] + (ll)f[v][j][1][1]));
            }
        size[u] += size[v];
    }
    return;
}

int main()
{
    n = read(), k = read();
    FOR(i, 1, n - 1)
        add(read(), read());
    dfs(1, 0);
    printf("%d\n", (f[1][k][0][1] + f[1][k][1][1]) % mod);
    return 0;
}