#include <cstdio>
#include <cstring>
#include <cmath>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, x) for (int i = x[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
#define il inline

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

const int maxn = 1005, maxm = 1e5 + 5;

const int INF = 1e9;

struct edge {
    int to, nxt;
    int w;
} e[maxm << 1];

int head[maxn], dep[maxn], cur[maxn], cnt = 1;
int s, t;

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

char str[25];
int r, c, d;

il int num(int i, int j, int k) {return (i - 1) * c + j + k * r * c;}

int main() {
    scanf("%d %d %d", &r, &c, &d);
    s = 2 * r * c + 1, t = s + 1;
    FOR(i, 1, r) {
        scanf("%s", str + 1);
        FOR(j, 1, c) {
            int w = str[j] - '0';
            if (!w) continue;
            add(num(i, j, 0), num(i, j, 1), w);
            FOR(ii, 1, r)
                FOR(jj, 1, c)
                    if ((i - ii) * (i - ii) + (j - jj) * (j - jj) <= d * d)
                        add(num(i, j, 1), num(ii, jj, 0), INF);
            if (i <= d || j <= d || (r - i + 1) <= d || (c - j + 1) <= d)
                add(num(i, j, 1), t, INF);
        }
    }
    int tot = 0;
    FOR(i, 1, r) {
        scanf("%s", str + 1);
        FOR(j, 1, c) {
            if (str[j] == 'L')
                add(s, num(i, j, 0), 1), ++tot;
        }
    }
    printf("%d\n", tot - dinic());
    return 0;
}