#include <cstdio>
#include <cctype>
#include <cstring>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, x) for (int i = x[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
#define il inline

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

const int maxn = 105, maxm = 20005;

const int INF = 1e9;

struct edge {
    int to, nxt, w;
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

char str[55][55];

int main() {
    int n, a1, a2, an, b1, b2, bn;
    while (~scanf("%d %d %d %d %d %d %d", &n, &a1, &a2, &an, &b1, &b2, &bn)) {
        ++a1, ++a2, ++b1, ++b2;
        s = n + 1, t = n + 2;
        memset(head, 0, sizeof head), cnt = 1;
        add(s, a1, an << 1), add(s, b1, bn << 1);
        add(a2, t, an << 1), add(b2, t, bn << 1);
        FOR(i, 1, n) scanf("%s", str[i] + 1);
        FOR(i, 1, n) {
            FOR(j, 1, n) {
                if (str[i][j] == 'O') add(i, j, 2);
                else if (str[i][j] == 'N') add(i, j, INF);
            }
        }
        int flag = 1;
        flag &= (dinic() == 2 * (an + bn));
        memset(head, 0, sizeof head), cnt = 1;
        add(s, a1, an << 1), add(s, b2, bn << 1);
        add(a2, t, an << 1), add(b1, t, bn << 1);
        FOR(i, 1, n) {
            FOR(j, 1, n) {
                if (str[i][j] == 'O') add(i, j, 2);
                else if (str[i][j] == 'N') add(i, j, INF);
            }
        }
        flag &= (dinic() == 2 * (an + bn));
        puts(flag ? "Yes" : "No");
    }
    return 0;
}