#include <cstdio>
#include <stack>
#include <queue>

const int maxn = 8e4 + 5, maxm = 2e5 + 5;
int n, m, st, head1[maxn], head2[maxn], tot;
int dfn[maxn], low[maxn], bel[maxn], times, scc, w[maxn];
bool ins[maxn];
std::stack<int> s;
std::queue<int> q;
int dis[maxn];
bool inq[maxn];

inline int max(int a, int b) {
    return a > b ? a : b;
}

inline int min(int a, int b) {
    return a < b ? a : b;
}

struct edge1 {
    int from, to, w, next, k;
}e1[maxm];

struct edge2 {
    int to, w, next;
}e2[maxm];

inline void add1(int u, int v, int w, int k) {
    e1[++tot].from = u;
    e1[tot].to = v;
    e1[tot].w = w;
    e1[tot].k = k;
    e1[tot].next = head1[u];
    head1[u] = tot;
    return;
}

inline void add2(int u, int v, int w) {
    e2[++tot].to = v;
    e2[tot].w = w;
    e2[tot].next = head2[u];
    head2[u] = tot;
    return;
}

inline int calc(int w, int k) {
    int ret = 0;
    while (w) {
        ret += w;
        w = w * k / 10;
    }
    return ret;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++times;
    s.push(u);
    ins[u] = 1;
    for (int i = head1[u]; i; i = e1[i].next) {
        int& v = e1[i].to;
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
        }
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        scc++;
        while (1) {
            int x = s.top();
            s.pop();
            ins[x] = 0;
            bel[x] = scc;
            if (x == u)
                break;
        }
    }
    return;
}

int spfa() {
    int ans = dis[st] = w[st];
    q.push(st);
    inq[st] = 1;
    while (!q.empty()) {
        int u = q.front();
        q.pop();
        inq[u] = 0;
        for (int i = head2[u]; i; i = e2[i].next) {
            int& v = e2[i].to, & d = e2[i].w;
            if (dis[u] + d + w[v] > dis[v]) {
                dis[v] = dis[u] + d + w[v];
                ans = max(dis[v], ans);
                if (!inq[v]) {
                    q.push(v);
                    inq[v] = 1;
                }
            }
        }
    }
    return ans;
}

int main() {
    scanf("%d %d", &n, &m);
    for (int i = 1; i <= m; i++) {
        int u, v, w; double k;
        scanf("%d %d %d %lf", &u, &v, &w, &k);
        add1(u, v, w, int(k * 10));
    }
    tot = 0;
    scanf("%d", &st);
    for (int i = 1; i <= n; i++)
        if (!dfn[i])
            tarjan(i);
    for (int i = 1; i <= m; i++) {
        if (bel[e1[i].from] == bel[e1[i].to])
            w[bel[e1[i].from]] += calc(e1[i].w, e1[i].k);
        else
            add2(bel[e1[i].from], bel[e1[i].to], e1[i].w);
    }
    st = bel[st];
    printf("%d\n", spfa());
    return 0;
}
