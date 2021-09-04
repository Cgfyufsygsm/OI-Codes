#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define GO(u, x) for (int i = x[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)

namespace fastIO {
const int maxc = 1 << 23;
char ibuf[maxc], *__p1 = ibuf, *__p2 = ibuf;
il char getchar() {return __p1 == __p2 && (__p2 = (__p1 = ibuf) + fread(ibuf, 1, maxc, stdin), __p1 == __p2) ? EOF : *__p1++;}
template<typename T> void read(T &n) {
    int x = 0; n = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        n = n * 10 + c - '0', c = getchar();
    n = x ? -n : n;
}
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

const int INF = 1e9;
const int maxn = 400 + 5, maxm = 5e5 + 5;

struct edge {
    int to, nxt;
    int w, c;
} e[maxm << 1];

int head[maxn], cnt = 1, s, t;

il void add(int u, int v, int w, int c) {
    e[++cnt].to = v, e[cnt].w = w, e[cnt].c = c;
    e[cnt].nxt = head[u], head[u] = cnt;
    e[++cnt].to = u, e[cnt].w = 0, e[cnt].c = -c;
    e[cnt].nxt = head[v], head[v] = cnt;
    return;
}

namespace MCMF {
int dis[maxn], flow[maxn], maxflow, mincost;
int pre[maxn], inq[maxn];

bool SPFA() {
    memset(inq, 0, sizeof inq);
    memset(dis, 0x3f, sizeof dis);
    std::queue<int> q;
    q.push(s);
    inq[s] = 1, dis[s] = 0;
    flow[s] = INF;
    while (!q.empty()) {
        int u = q.front(); q.pop();
        inq[u] = 0;
        GO(u, head) {
            if (e[i].w > 0 && dis[u] + e[i].c < dis[v]) {
                dis[v] = dis[u] + e[i].c;
                flow[v] = min(flow[u], e[i].w);
                pre[v] = i;
                if (!inq[v]) {
                    inq[v] = 1;
                    q.push(v);
                }
            }
        }
    }
    return dis[t] < INF;
}

void update() {
    int now = t;
    while (now != s) {
        int i = pre[now];
        e[i].w -= flow[t], e[i ^ 1].w += flow[t];
        now = e[i ^ 1].to;
    }
    maxflow += flow[t];
    mincost += flow[t] * dis[t];
    return;
}

void MCMF() {
    while (SPFA()) update();
    return;
}
} // namespace MCMF

int f[205][205], dt[205][205];

struct requirement {
    int a, b, s, t, c;
} q[205];

int main() {
    int n, m, k, T;
    read(n), read(m), read(k), read(T);
    FOR(i, 1, n) FOR(j, 1, n) read(dt[i][j]);
    FOR(i, 1, n) FOR(j, 1, n) read(f[i][j]);
    FOR(i, 1, m) read(q[i].a), read(q[i].b), read(q[i].s), read(q[i].t), read(q[i].c), ++q[i].a, ++q[i].b;
    //要求入：1-m，出：m + 1-2m，超级源：2m + 1, 源：2m + 2, 超级汇：2m + 3
    int ss = 2 * m + 2;
    s = 2 * m + 1, t = 2 * m + 3;
    add(s, ss, k, 0);
    FOR(i, 1, m) {
        add(i, i + m, 1, -q[i].c);
        if (q[i].t + dt[q[i].b][1] <= T) add(i + m, t, INF, f[q[i].b][1]);
        else continue;
        if (q[i].s >= dt[1][q[i].a]) add(ss, i, INF, f[1][q[i].a]);
        FOR(j, 1, m)
            if (q[i].t + dt[q[i].b][q[j].a] <= q[j].s)
                add(i + m, j, INF, f[q[i].b][q[j].a]);
    }
    MCMF::MCMF();
    print(-MCMF::mincost);
    return output(), 0;
}