#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (ll i = a; i <= b; ++i)

typedef long long ll;

ll read()
{
    ll s = 0; int x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10ll + c - '0', c = getchar();
    return x ? -s : s;
}

inline ll max(ll a, ll b) {return a > b ? a : b;}
inline ll min(ll a, ll b) {return a < b ? a : b;}

const int maxn = 2005;

int n;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
ll w[maxn << 1], size[maxn], f[maxn][maxn], m, tmp[maxn];

void add(int u, int v, ll dis)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    w[cnt] = dis;
    head[u] = cnt;
    return;
}

void dfs(int u, int fa)
{
    size[u] = 1;
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        FOR(k, 0, m) tmp[k] = 0;
        FOR(a, 0, min(size[u], m))
            FOR(b, 0, min(size[v], m))
                if (a + b <= m)
                {
                    ll val = b * (m - b) + (size[v] - b) * (n - m - size[v] + b);
                    tmp[a + b] = max(tmp[a + b], f[u][a] + f[v][b] + val * w[i]);
                }
        FOR(k, 0, m)
            f[u][k] = tmp[k];
        size[u] += size[v];
    }
    return;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, n - 1)
    {
        int u = read(), v = read(), d = read();
        add(u, v, d), add(v, u, d);
    }
    dfs(1, 0);
    printf("%lld\n", f[1][m]);
    return 0;
}