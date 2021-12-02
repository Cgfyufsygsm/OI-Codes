#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define GO(u, x) for (int i = x[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)
#define il inline

using namespace std;

const int maxn = 10005, maxm = 2e5 + 5;
const int INF = 1e9;

struct edge {
    int to, nxt, w;
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

char str[105][105];
int n, m;
const int fx[] = {0, 0, 1, -1};
const int fy[] = {1, -1, 0, 0};
bool vis[maxn], ans[105][105];
using pii = pair<int, int>;
pii decode[maxn];

il int encode(int i, int j) {return (i - 1) * m + j;}

void dfs2(int u, int col) {
    if (vis[u]) return;
    vis[u] = 1;
    int x = decode[u].first, y = decode[u].second;
    if (((x + y) & 1) == col) ans[x][y] = 1;
    GO(u, head) {
        if (e[i].w != col || v == s || v == t) continue;
        dfs2(v, col);
    }
    return;
}

int main() {
    scanf("%d %d", &n, &m);
    FOR(i, 1, n) scanf("%s", str[i] + 1);
    s = n * m + 1, t = n * m + 2;
    int tot = 0;
    FOR(i, 1, n) FOR(j, 1, m) if (str[i][j] != '#') {
        ++tot, decode[encode(i, j)] = pii(i, j);
        if ((i + j) & 1) add(s, encode(i, j), 1);
        else add(encode(i, j), t, 1);
    }
    FOR(i, 1, n) FOR(j, 1, m) if (str[i][j] != '#' && ((i + j) & 1)) {
        FOR(k, 0, 3) {
            int tx = i + fx[k], ty = j + fy[k];
            if (tx < 1 || tx > n || ty < 1 || ty > n || str[tx][ty] == '#') continue;
            add(encode(i, j), encode(tx, ty), 1);
        }
    }
    int flow = dinic();
    if (flow * 2 == tot) return puts("LOSE"), 0;
    puts("WIN");
    dfs2(s, 1);
    memset(vis, 0, sizeof vis);
    dfs2(t, 0);
    FOR(i, 1, n) FOR(j, 1, m) if (str[i][j] == '.' && ans[i][j]) printf("%d %d\n", i, j);
    return 0;
}