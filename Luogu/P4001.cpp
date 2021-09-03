#include <cstdio>
#include <cctype>
#include <utility>
#include <cstring>
#include <queue>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

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
using namespace std;


const int maxn = 2e6 + 5, maxm = 7e6 + 5;
int s, t;
struct edge {
    int to, nxt, w;
} e[maxm];
int head[maxn], cnt;
int dis[maxn], vis[maxn];

priority_queue<pair<int, int>, vector<pair<int, int> >, greater<pair<int, int> > > q;

int dijkstra() {
    memset(dis, 0x3f, sizeof dis);
    dis[s] = 0;
    q.push(make_pair(0, s));
    while (!q.empty()) {
        int u = q.top().second;
        q.pop();
        if (!vis[u]) {
            vis[u] = 1;
            for (int i = head[u]; i; i = e[i].nxt) {
                int v = e[i].to, w = e[i].w;
                if (dis[u] + w < dis[v]) {
                    dis[v] = dis[u] + w;
                    q.push(make_pair(dis[v], v));
                }
            }
        }
    }
    return dis[t];
}

int n, m;

il int num(int i, int j, int k) {return 2 * ((i - 1) * (m - 1) + j - 1) + k;}

il void add(int u, int v, int w) {
    e[++cnt].to = v, e[cnt].w = w, e[cnt].nxt = head[u], head[u] = cnt;
    e[++cnt].to = u, e[cnt].w = w, e[cnt].nxt = head[v], head[v] = cnt;
    return;
}

int main() {
    read(n), read(m);
    s = 2 * (n - 1) * (m - 1) + 1, t = s + 1;
    FOR(i, 1, n) {
        FOR(j, 1, m - 1) {
            int w; read(w);
            if (i == 1) add(s, num(1, j, 1), w);
            else if (i == n) add(num(n - 1, j, 2), t, w);
            else add(num(i - 1, j, 2), num(i, j, 1), w);
        }
    }
    FOR(i, 1, n - 1) {
        FOR(j, 1, m) {
            int w; read(w);
            if (j == 1) add(num(i, j, 2), t, w);
            else if (j == m) add(s, num(i, m - 1, 1), w);
            else add(num(i, j - 1, 1), num(i, j, 2), w);
        }
    }
    FOR(i, 1, n - 1) {
        FOR(j, 1, m - 1) {
            int w; read(w);
            add(num(i, j, 1), num(i, j, 2), w);
        }
    }
    print(dijkstra());
    return output(), 0;
}