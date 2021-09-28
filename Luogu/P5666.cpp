#include <cstdio>
#include <cctype>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define GO(i, u) for (int i = head[u], v = to[i]; i; i = nxt[i], v = to[i])

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

const int maxn = 3e5 + 5;
int n, head[maxn], to[maxn << 1], nxt[maxn << 1], cnt;
int son1[maxn], son2[maxn], size[maxn], f[maxn][19];
long long ans;

il void add(int u, int v) {
    to[++cnt] = v;
    nxt[cnt] = head[u];
    head[u] = cnt;
    return;
}

void reset(int u) {
    for (int d = 1; f[u][d]; ++d) f[u][d] = 0;
    f[u][0] = son1[u];
    for (int d = 1; f[u][d - 1]; ++d) f[u][d] = f[f[u][d - 1]][d - 1];
    return;
}

void dfs1(int u, int fa) {
    size[u] = 1;
    son1[u] = son2[u] = 0;
    GO(i, u) {
        if (v == fa) continue;
        dfs1(v, u);
        size[u] += size[v];
        if (size[v] > size[son1[u]])
            son2[u] = son1[u], son1[u] = v;
        else if (size[v] > size[son2[u]])
            son2[u] = v;
    }
    reset(u);
    return;
}

void calc(int u) {
    int d, p = u;
    for (d = 0; f[u][d]; ++d);
    while ((--d) >= 0) {
        if ((size[f[p][d]] << 1) > size[u])
            p = f[p][d];
    }
    ans += p;
    if (f[p][0] && (size[f[p][0]] << 1) >= size[u])
        ans += f[p][0];
    return;
}

void dfs2(int u, int fa) {
    int son0 = son1[u], size0 = size[u];
    GO(i, u) {
        if (v == fa) continue;
        calc(v);
        size[u] = n - size[v];
        son1[u] = son0 == v ? son2[u] : son0;
        if (size[son1[u]] < n - size0) son1[u] = fa;
        reset(u);
        calc(u);
        dfs2(v, u);
    }
    son1[u] = son0, size[u] = size0;
    reset(u);
}

int main() {
    int T; read(T);
    while (T--) {
        memset(head, 0, sizeof head);
        cnt = 0, ans = 0;
        read(n);
        FOR(i, 1, n - 1) {
            int u, v; read(u), read(v);
            add(u, v), add(v, u);
        }
        dfs1(1, 0);
        dfs2(1, 0);
        print(ans), putchar('\n');
    }
    return output(), 0;
}