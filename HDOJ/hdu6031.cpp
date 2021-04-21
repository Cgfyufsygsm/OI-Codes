#include <cstdio>
#include <cctype>
#include <cstring>
#include <set>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1e5 + 5;

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

inline int max(int a, int b) {return a > b ? a : b;}

int n, m;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
int maxdep, dep[maxn], fa[maxn][22];

inline void add(int u, int v)
{
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void dfs(int u, int father)
{
    dep[u] = dep[father] + 1;
    maxdep = max(dep[u], maxdep);
    fa[u][0] = father;
    FOR(i, 1, 18)
        fa[u][i] = fa[fa[u][i - 1]][i - 1];
    for (int i = head[u]; i; i = nxt[i])
    {
        int v = to[i];
        if (v == father) continue;
        dfs(v, u);
    }
    return;
}

int A[maxn], B[maxn];

int find(int u, int dep)
{
    if (dep == 0) return u;
    DEC(i, 19, 0)
        if (dep & (1 << i))
            u = fa[u][i];
    return u;
}

bool check(int mid)
{
    std::set<int> s;
    FOR(i, 1, A[0])
    {
        if (dep[A[i]] < mid) continue;
        int anc = find(A[i], dep[A[i]] - mid);
        s.insert(anc);
    }
    FOR(i, 1, B[0])
    {
        if (dep[B[i]] < mid) continue;
        int anc = find(B[i], dep[B[i]] - mid);
        if (s.count(anc)) return 1;
    }
    return 0;
}

int main()
{
    while (scanf("%d %d", &n, &m) == 2)
    {
        memset(head, 0, sizeof head);
        maxdep = 0, cnt = 0;
        FOR(i, 1, n - 1)
        {
            int u = read(), v = read();
            add(u, v);
            add(v, u);
        }
        dfs(1, 0);
        FOR(i, 1, m)
        {
            A[0] = read();
            FOR(i, 1, A[0])
                A[i] = read();
            B[0] = read();
            FOR(i, 1, B[0])
                B[i] = read();
            int l = 1, r = maxdep, mid, ans;
            while (l <= r)
            {
                mid = (l + r) >> 1;
                if (check(mid))
                    ans = mid, l = mid + 1;
                else r = mid - 1;
            }
            printf("%d\n", ans);
        }
    }
    return 0;
}