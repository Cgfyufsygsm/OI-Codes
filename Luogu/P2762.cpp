#include <iostream>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, x) for (int i = x[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
#define il inline

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

const int maxn = 205, maxm = 5005;

const int INF = 1e9;

struct edge {
    int to, nxt;
    int w;
} e[maxm << 1];

int head[maxn], dep[maxn], cur[maxn], cnt = 1;
int n, m, s, t;

il void add(int u, int v, int w) {
    e[++cnt].to = v;
    e[cnt].w = w;
    e[cnt].nxt = head[u];
    head[u] = cnt;
    e[++cnt].to = u;
    e[cnt].w = 0;
    e[cnt].nxt = head[v];
    head[v] = cnt;
    return;
}

bool bfs() {
    static int q[maxn], qhead, qtail;
    memset(dep, -1, sizeof dep);
    memcpy(cur, head, sizeof head);
    q[qhead = qtail = 1] = s;
    dep[s] = 0;
    while (qhead <= qtail) {
        int u = q[qhead++];
        GO(u, head) {
            if (e[i].w > 0 && dep[v] == -1) {
                q[++qtail] = v;
                dep[v] = dep[u] + 1;
                if (v == t) return true;
            }
        }
    }
    return false;
}

int dfs(int u, int in) {
    if (u == t) return in;
    int out = 0;
    GO(u, cur) {
        cur[u] = i;
        if (e[i].w > 0 && dep[v] == dep[u] + 1) {
            int res = dfs(v, min(in, e[i].w));
            e[i].w -= res, e[i ^ 1].w += res;
            in -= res, out += res;
        }
        if (!in) break;
    }
    if (!out) dep[u] = -1;
    return out;
}

int dinic() {
    int ret = 0;
    while (bfs()) ret += dfs(s, INF);
    return ret;
}

char tools[10000];

int main() {
    scanf("%d %d", &m, &n);
    s = n + m + 1, t = n + m + 2;
    int sum = 0;
    FOR(i, 1, m) {
        int cost; scanf("%d", &cost);
        sum += cost;
        add(s, i, cost);
        memset(tools, 0, sizeof tools);
        std::cin.getline(tools, 10000);
        int ulen = 0, tool;
        while (sscanf(tools + ulen, "%d", &tool) == 1) {
            add(i, tool + m, INF);
            if (tool == 0)
                ulen++;
            else {
                while (tool) {
                    tool /= 10;
                    ulen++;
                }
            }
            ulen++;
        }
    }
    FOR(i, 1, n) {
        int tmp; scanf("%d", &tmp);
        add(m + i, t, tmp);
    }
    sum -= dinic();
    FOR(i, 1, m) if (dep[i] >= 0) printf("%d ", i);
    puts("");
    FOR(i, 1, n) if (dep[i + m] >= 0) printf("%d ", i);
    printf("\n%d\n", sum);
    return 0;
}