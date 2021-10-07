#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}

const int maxn = 50005, maxm = 1e5 + 5;
int head[maxn], cnte, n, m;
struct edge {
    int to, nxt, w;
} e[maxm];

il void add(int u, int v, int w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

int dfn[maxn], low[maxn], ins[maxn], stk[maxn], top;
int dfnClock, scc[maxn], sccCnt;
int res[maxn];

void tarjan(int u) {
    dfn[u] = low[u] = ++dfnClock;
    stk[++top] = u, ins[u] = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (!dfn[v]) tarjan(v), low[u] = min(low[u], low[v]);
        else if (ins[v]) low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++sccCnt;
        while (1) {
            int now = stk[top--];
            ins[now] = 0;
            scc[now] = sccCnt;
            if (now == u) break;
        }
    }
    return;
}

int main() {
    while (~scanf("%d %d", &n, &m)) {
        memset(head, 0, sizeof head), cnte = 0;
        memset(dfn, 0, sizeof dfn), sccCnt = dfnClock = 0;
        memset(res, 0x3f, sizeof res);
        FOR(i, 1, m) {
            int u, v, c;
            scanf("%d %d %d", &u, &v, &c);
            add(u + 1, v + 1, c);
        }
        FOR(i, 1, n) if (!dfn[i]) tarjan(i);
        FOR(u, 1, n) {
            for (int i = head[u]; i; i = e[i].nxt) {
                int &v = e[i].to;
                if (scc[u] == scc[v]) continue;
                res[scc[v]] = min(res[scc[v]], e[i].w);
            }
        }
        int ans = 0;
        FOR(i, 1, sccCnt) {
            if (scc[1] == i) continue;
            ans += res[i];
        }
        printf("%d\n", ans);
    }
    return 0;
}