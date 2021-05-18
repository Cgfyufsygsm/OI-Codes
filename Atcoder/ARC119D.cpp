#include <cstdio>
#include <cstring>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define GO(u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

const int maxn = 2500 + 5, maxm = 2 * maxn * maxn + 5;

int h, w;

int head[maxn << 1], to[maxm], nxt[maxm], cnte;

void add(int u, int v)
{
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

int bel[maxn << 1], vis[maxn << 1], L[maxn << 1], R[maxn << 1];

void color(int u, int fa, int c)
{
    if (bel[u]) return;
    bel[u] = c;
    u > h ? ++R[c] : ++L[c];
    GO(u) if (v != fa) color(v, u, c);
    return;
}

int calced[maxn];

char type[maxm];
int X[maxm], Y[maxm], ans;

void dfs(int u, int fa)
{
    vis[u] = 1;
    GO(u)
    {
        if (vis[v] || v == fa) continue;
        dfs(v, u);
        ++ans;
        type[ans] = v > h ? 'Y' : 'X';
        X[ans] = u > v ? v : u;
        Y[ans] = u > v ? u - h : v - h;
    }
    return;
}

int main()
{
    scanf("%d %d", &h, &w);
    FOR(i, 1, h)
    {
        char s[maxn];
        scanf("%s", s + 1);
        FOR(j, 1, w)
        {
            if (s[j] == 'R')
                add(i, j + h), add(j + h, i);
        }
    }
    int cccnt = 0, sumr = 0, sumc = 0;
    FOR(i, 1, h)
    {
        if (bel[i]) continue;
        if (!to[head[i]]) continue;
        else color(i, 0, ++cccnt), sumr += L[cccnt], sumc += R[cccnt];
    }
    int mintmp = h * w, resr, resc;
    for (int r = 0, c = cccnt; r <= cccnt; ++r, --c)
        if ((h - sumr + r) * (w - sumc + c) < mintmp)
            resr = r, resc = c, mintmp = (h - sumr + r) * (w - sumc + c);
    FOR(i, 1, h + w)
    {
        if (L[bel[i]] + R[bel[i]] <= 1 || calced[bel[i]]) continue;
        if (resr && i <= h) dfs(i, 0), resr--, calced[bel[i]] = 1;
        else if (resc && i > h) dfs(i, 0), resc--, calced[bel[i]] = 1; 
    }
    printf("%d\n", ans);
    FOR(i, 1, ans) printf("%c %d %d\n", type[i], X[i], Y[i]);
    return 0;
}