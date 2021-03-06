#include <cstdio>
#include <cctype>
#include <cstring>
#include <queue>
#include <algorithm>
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
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}// namespace fastIO

using namespace fastIO;

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

typedef long long ll;
const ll INF = 1e18;
const int maxn = 1 << 20 | 5, maxm = maxn << 1 | 5;

struct edge {
    int to, nxt;
    ll w, c;
} e[maxm << 1];

int head[maxn], cnt = 1, s, t;

il void add(int u, int v, ll w, ll c) {
    //printf("add %d %d: %lld %lld\n", u, v, w, c);
    e[++cnt].to = v, e[cnt].w = w, e[cnt].c = c;
    e[cnt].nxt = head[u], head[u] = cnt;
    e[++cnt].to = u, e[cnt].w = 0, e[cnt].c = -c;
    e[cnt].nxt = head[v], head[v] = cnt;
    return;
}

namespace MCMF {
ll dis[maxn], flow[maxn], maxflow, mincost;
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

struct edge0 {
    int u, v, w;
} e0[maxn * 20];
int cnte0;

int a[maxn], n, k, popcnt[maxn], vis[maxn];

int main() {
    read(n), read(k);
    FOR(i, 0, (1 << n) - 1) read(a[i]), popcnt[i] = popcnt[i >> 1] + (i & 1);
    FOR(i, 0, (1 << n) - 1)
        FOR(j, 0, n - 1)
            if (i & (1 << j))
                e0[++cnte0] = {i, i ^ (1 << j), a[i] + a[i ^ (1 << j)]};
    std::nth_element(e0 + 1, e0 + min(cnte0, k * (2 * n - 1)), e0 + cnte0 + 1, [](const edge0 &a, const edge0 &b) -> bool {return a.w > b.w;});
    //FOR(i, 1, cnte0) printf("%d %d %d\n", e0[i].u, e0[i].v, e0[i].w);
    int ss = 1 << n;
    s = ss + 1, t = s + 1;
    add(s, ss, k, 0);
    FOR(i, 1, min(cnte0, k * (2 * n - 1))) {
        if (popcnt[e0[i].u] & 1) add(e0[i].u, e0[i].v, 1, -e0[i].w);
        else add(e0[i].v, e0[i].u, 1, -e0[i].w);
        if (!vis[e0[i].u]) {
            if (popcnt[e0[i].u] & 1) add(ss, e0[i].u, 1, 0);
            else add(e0[i].u, t, 1, 0);
            vis[e0[i].u] = 1;
        }
        if (!vis[e0[i].v]) {
            if (popcnt[e0[i].v] & 1) add(ss, e0[i].v, 1, 0);
            else add(e0[i].v, t, 1, 0);
            vis[e0[i].v] = 1;
        }
    }
    MCMF::MCMF();
    print(-MCMF::mincost, '\n');
    return output(), 0;
}