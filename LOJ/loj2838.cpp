#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e5 + 3, maxm = 2e5 + 5, sqrt = 250;
int n, m, Q;
int head[maxn], cnte, to[maxm], nxt[maxm];

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

struct node {
    int u, w;
    node() {}
    node(int _u, int _w) : u(_u), w(_w) {}
    il bool operator<(const node &b) const {return w < b.w;}
    il node operator+(const int &x) {return node(u, w + x);}
} f0[maxn][sqrt + 3], tmp[sqrt + 5];
int cnt[maxn];

int c[maxn], f[maxn], vis[maxn];

int main() {
    read(n), read(m), read(Q);
    while (m--) {
        int s, t; read(s), read(t);
        add(s, t);
    }
    FOR(i, 1, n) f0[i][cnt[i] = 1] = node(i, 0);
    FOR(u, 1, n) {
        for (int i = head[u]; i; i = nxt[i]) {
            int &v = to[i];
            int p1 = 1, p2 = 1, j = 1;
            while (j <= sqrt && p1 <= cnt[u] && p2 <= cnt[v]) {
                while (p1 <= cnt[u] && vis[f0[u][p1].u]) ++p1;
                while (p2 <= cnt[v] && vis[f0[v][p2].u]) ++p2;
                if (p1 <= cnt[u] && f0[u][p1] + 1 < f0[v][p2])
                    vis[f0[v][p2].u] = 1, tmp[j++] = f0[v][p2++];
                else if (p2 <= cnt[v])
                    vis[f0[u][p1].u] = 1, tmp[j++] = f0[u][p1++] + 1;
            }
            while (j <= sqrt && p1 <= cnt[u]) {
                while (p1 <= cnt[u] && vis[f0[u][p1].u]) ++p1;
                if (p1 <= cnt[u]) vis[f0[u][p1].u] = 1, tmp[j++] = f0[u][p1++] + 1;
            }
            while (j <= sqrt && p2 <= cnt[v]) {
                while (p2 <= cnt[v] && vis[f0[v][p2].u]) ++p2;
                if (p2 <= cnt[v]) vis[f0[v][p2].u] = 1, tmp[j++] = f0[v][p2++];
            }
            FOR(k, 1, j - 1) f0[v][k] = tmp[k], vis[f0[v][k].u] = 0;
            cnt[v] = j - 1;
        }
    }
    FOR(kase, 1, Q) {
        int t, y; read(t), read(y);
        FOR(i, 1, y) {
            int c; read(c);
            vis[c] = kase;
        }
        if (y < sqrt) {
            int ans = -1;
            FOR(i, 1, cnt[t]) if (vis[f0[t][i].u] != kase) {
                ans = f0[t][i].w;
                break;
            }
            print(ans, '\n');
        } else {
            memset(f, -1, sizeof f);
            FOR(u, 1, n) {
                if (vis[u] != kase) chkmax(f[u], 0);
                if (f[u] < 0) continue;
                for (int i = head[u]; i; i = nxt[i]) {
                    int &v = to[i];
                    chkmax(f[v], f[u] + 1);
                }
            }
            print(f[t], '\n');
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}