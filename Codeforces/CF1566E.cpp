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

const int maxn = 2e5 + 5;

int n, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte, d[maxn], k;

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u, int fa) {
    bool flag = 0;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        if (d[v] == 2) flag = 1;
    }
    if (fa) {
        if (flag) ++k, d[u] = 3;
        else d[u] = 2;
    }
    return;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) head[i] = d[i] = 0;
        k = 0;
        FOR(i, 1, n - 1) {
            int u, v; read(u), read(v);
            add(u, v), add(v, u);
        }
        dfs(1, 0);
        int s = 0;
        for (int i = head[1]; i; i = nxt[i])
            if (d[to[i]] == 2) {s = 1; break;}
        print(n - 2 * k - s), putchar('\n');
    }
    return output(), 0;
}