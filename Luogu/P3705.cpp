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

using db = double;
const int INF = 1e9;
const int maxn = 205 + 5, maxm = 5e4 + 5;

struct edge {
    int to, nxt, w;
    db c;
} e[maxm << 1];

int head[maxn], cnt = 1, s, t;

il void add(int u, int v, int w, db c) {
    e[++cnt].to = v, e[cnt].w = w, e[cnt].c = c;
    e[cnt].nxt = head[u], head[u] = cnt;
    e[++cnt].to = u, e[cnt].w = 0, e[cnt].c = -c;
    e[cnt].nxt = head[v], head[v] = cnt;
    return;
}

namespace MCMF {
db dis[maxn], mincost;
int flow[maxn], maxflow;
int pre[maxn], inq[maxn];

bool SPFA() {
    memset(inq, 0, sizeof inq);
    memset(dis, 127, sizeof dis);
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

int a[maxn][maxn], b[maxn][maxn], n;

void build(db mid) {
    cnt = 1, s = 2 * n + 1, t = s + 1;
    MCMF::mincost = 0, MCMF::maxflow = 0;
    memset(head, 0, sizeof head);
    FOR(i, 1, n) add(s, i, 1, 0), add(i + n, t, 1, 0);
    FOR(i, 1, n) FOR(j, 1, n) add(i, j + n, 1, mid * b[i][j] - a[i][j]);
    return;
}

bool check(db mid) {
    build(mid);
    MCMF::MCMF();
    return MCMF::mincost <= 0;
}

int main() {
    read(n);
    db maxa = 0, minb = INF;
    FOR(i, 1, n) FOR(j, 1, n) read(a[i][j]), maxa = max(maxa, (db)a[i][j]);
    FOR(i, 1, n) FOR(j, 1, n) read(b[i][j]), minb = min(minb, (db)b[i][j]);
    db l = 0, r = maxa / minb, ans;
    while (r - l > 1e-8) {
        db mid = (l + r) / 2;
        if (check(mid)) ans = mid, l = mid;
        else r = mid;
    }
    printf("%.6lf\n", ans);
    return output(), 0;
}