#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 5005, maxm = 2e5 + 5;

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

int n, m;
int u[maxm], v[maxm], w[maxm];

int fa[maxn], best[maxn];
bool used[maxm];

inline int find(int u)
{
    return u == fa[u] ? u : fa[u] = find(fa[u]);
}

inline bool better(int i, int j)
{
    if (!j) return 1;
    if (w[i] != w[j]) return w[i] < w[j];
    return i < j;
}

int main()
{
    n = read(), m = read();
    FOR(i, 1, m)
        u[i] = read(), v[i] = read(), w[i] = read();
    FOR(i, 1, n) fa[i] = i;
    int merged = 0, ans = 0;
    bool update = 1;
    while (update)
    {
        update = 0;
        memset(best, 0, sizeof best);
        FOR(i, 1, m)
        {
            if (used[i]) continue;
            int p = find(u[i]), q = find(v[i]);
            if (p == q) continue;
            if (better(i, best[p])) best[p] = i;
            if (better(i, best[q])) best[q] = i;
        }
        FOR(i, 1, n)
            if (best[i] && !used[best[i]])
            {
                update = 1;
                ++merged, ans += w[best[i]];
                used[best[i]] = 1;
                fa[find(u[best[i]])] = find(v[best[i]]);
            }
    }
    if (merged == n - 1) printf("%d\n", ans);
    else puts("orz");
    return 0;
}