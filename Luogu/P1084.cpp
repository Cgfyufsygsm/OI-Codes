#include <bits/stdc++.h>
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
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = 50000 + 5;

struct edge {
    int to, nxt;
    ll w;
} e[maxn << 1];

int n, m, head[maxn], cnte, p0[maxn];
int fa[maxn][17];
ll d[maxn][17];
bool vis[maxn], need0[maxn];

il void add(int u, int v, int w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

void getfa(int u, int f, int lastid) {
    fa[u][0] = f, d[u][0] = e[lastid].w;
    FOR(j, 1, 16) fa[u][j] = fa[fa[u][j - 1]][j - 1], d[u][j] = d[fa[u][j - 1]][j - 1] + d[u][j - 1];
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == f) continue;
        getfa(v, u, i);
    }
    return;
}

using pii = std::pair<ll, int>;
std::vector<pii> army0;
std::vector<ll> army, need;

void jump(int u, ll mid) {
    DEC(j, 16, 0) {
        if (d[u][j] <= mid && fa[u][j] > 1) {
            mid -= d[u][j];
            u = fa[u][j];
        }
    }
    if (fa[u][0] == 1 && mid >= d[u][0]) army0.push_back(pii(mid - d[u][0], u));
    else vis[u] = 1;
    return;
}

bool dfs(int u) {
    if (vis[u]) return true;
    bool isleaf = 1;
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == fa[u][0]) continue;
        isleaf = 0;
        if (!dfs(v)) return false;
    }
    if (isleaf) return false;
    return true;
}

bool check(ll mid) {
    memset(vis, 0, sizeof vis);
    memset(need0, 0, sizeof need0);
    need.clear(), army.clear(), army0.clear();

    FOR(i, 1, m) jump(p0[i], mid);

    for (int i = head[1]; i; i = e[i].nxt) if (!dfs(e[i].to)) need0[e[i].to] = 1;

    std::sort(army0.begin(), army0.end());
    for (auto p : army0) {
        if (need0[p.second] && p.first < d[p.second][0])
            need0[p.second] = 0;
        else army.push_back(p.first);
    }

    for (int i = head[1]; i; i = e[i].nxt) if (need0[e[i].to]) need.push_back(d[e[i].to][0]);

    if (army.size() < need.size()) return false;
    std::sort(need.begin(), need.end());
    std::sort(army.begin(), army.end());
    int i = 0, j = 0;
    for (; i < (int)army.size() && j < (int)need.size(); ++i) {
        if (army[i] >= need[j]) ++j;
    }
    return j >= (int)need.size();
}

int main() {
    read(n);
    int deg1 = 0;
    FOR(i, 1, n - 1) {
        int u, v, w;
        read(u), read(v), read(w);
        add(u, v, w), add(v, u, w);
        if (u == 1 || v == 1) ++deg1;
    }
    read(m);
    FOR(i, 1, m) read(p0[i]);

    if (deg1 > m) return print(-1, '\n'), output(), 0;

    getfa(1, 0, 0);

    ll l = 1, r = 5.5e13, ans = 0;
    while (l <= r) {
        ll mid = (l + r) >> 1ll;
        if (check(mid)) ans = mid, r = mid - 1;
        else l = mid + 1;
    }
    print(ans, '\n');
    return output(), 0;
}