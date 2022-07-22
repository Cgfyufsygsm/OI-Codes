#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define GO(u, x) for (int i = x[u], v = e[i].to; i; i = e[i].nxt, v = e[i].to)

using namespace std;

namespace YangTY {

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int INF = 1e9;
const int maxn = 5e3 + 5, maxm = 5e4 + 5;

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

int r, c, id1[25][25], id2[25][25], tot, dir[256];
char mp[20][20];

const int fx[] = {0, 0, -1, 1};
const int fy[] = {-1, 1, 0, 0}; // LRUD

int main() {
    cin >> r >> c;
    s = 1, t = tot = 2;
    FOR(i, 1, r) {
        cin >> &mp[i][1];
        FOR(j, 1, c) id1[i][j] = ++tot, id2[i][j] = ++tot;
    }
    dir['L'] = 0, dir['R'] = 1, dir['U'] = 2, dir['D'] = 3;
    FOR(i, 1, r) FOR(j, 1, c) {
        add(s, id1[i][j], 1, 0);
        add(id2[i][j], t, 1, 0);
        FOR(k, 0, 3) {
            int x = i + fx[k], y = j + fy[k];
            if (x < 1) x = r;
            if (x > r) x = 1;
            if (y < 1) y = c;
            if (y > c) y = 1;
            add(id1[i][j], id2[x][y], 1, dir[mp[i][j]] != k);
        }
    }
    MCMF::MCMF();
    cout << MCMF::mincost << endl;
    return 0;
}
} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}