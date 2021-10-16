#include <cstdio>
#include <cctype>
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

const int maxn = 2e5 + 5, maxm = 5e5 + 5;

int n, a, b, ans = 1e9;

namespace BlockForest {
int head[maxn << 1], to[maxn << 2], nxt[maxn << 2], cnte;
int fang;

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

bool dfs(int u, int fa) {
    if (u == b) return true;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa) continue;
        if (dfs(v, u) && u != a) {
            ans = min(u, ans);
            return true;
        }
    }
    return false;
}
}

namespace G0 {
int head[maxn], to[maxm << 1], nxt[maxm << 1], cnte;
int dfn[maxn], low[maxn], dfnClock, stk[maxn], top;

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void tarjan(int u) {
    dfn[u] = low[u] = ++dfnClock;
    stk[++top] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (!dfn[v]) {
            tarjan(v);
            low[u] = min(low[u], low[v]);
            if (dfn[u] == low[v]) {
                using BlockForest::add;
                using BlockForest::fang;
                ++BlockForest::fang;
                while (true) {
                    int x = stk[top--];
                    add(x, fang), add(fang, x);
                    if (x == v) break;
                }
                add(u, fang), add(fang, u);
            }
        } else low[u] = min(low[u], dfn[v]);
    }
    return;
}
}

int main() {
    read(n);
    int u, v;
    read(u), read(v);
    while (u && v) {
        G0::add(u, v), G0::add(v, u);
        read(u), read(v);
    }
    read(a), read(b);
    BlockForest::fang = n;
    G0::tarjan(a);
    if (!G0::dfn[b]) return puts("No solution"), 0;
    BlockForest::dfs(a, 0);
    ans <= n ? print(ans, '\n') : (void)puts("No solution");
    return output(), 0;
}