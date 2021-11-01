#include <cstdio>
#include <cctype>
#include <vector>
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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e5 + 5, maxm = 2e5 + 5;
int n, m;
int u0[maxm], v0[maxm], deg[maxn], tag[maxn];
std::vector<int> G[maxn];

il bool cmp(int u, int v) {
    return deg[u] != deg[v] ? deg[u] < deg[v] : u < v;
}

int main() {
    read(n), read(m);
    FOR(i, 1, m) {
        read(u0[i]), read(v0[i]);
        ++deg[u0[i]], ++deg[v0[i]];
    }
    FOR(i, 1, m) {
        if (cmp(u0[i], v0[i])) G[u0[i]].push_back(v0[i]);
        else G[v0[i]].push_back(u0[i]);
    }
    int ans = 0;
    FOR(u, 1, n) {
        for (auto &v : G[u]) tag[v] = u;
        for (auto &v : G[u]) for (auto &w : G[v]) if (tag[w] == u) ++ans;
    }
    print(ans, '\n');
    return output(), 0;
}