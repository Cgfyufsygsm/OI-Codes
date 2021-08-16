#include <cstdio>
#include <cctype>
#include <algorithm>
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
}

using namespace fastIO;

typedef long long ll;

const int maxn = 1e5 + 5;

struct edge {
    int u, v, w;
    il bool operator<(const edge &rhs) const {return w < rhs.w;}
} e[maxn];

int fa[maxn], size[maxn], n;

il int find(int u) {return u == fa[u] ? u : fa[u] = find(fa[u]);}
il void merge(int u, int v) {
    u = find(u), v = find(v);
    size[u] += size[v];
    fa[v] = u;
    return;
}

int main() {
    read(n);
    FOR(i, 1, n - 1)
        read(e[i].u), read(e[i].v), read(e[i].w);
    FOR(i, 1, n) fa[i] = i, size[i] = 1;
    std::sort(e + 1, e + n);
    ll ans = 0;
    FOR(i, 1, n - 1) {
        ans += 1ll * size[find(e[i].u)] * size[find(e[i].v)] * e[i].w;
        merge(e[i].u, e[i].v); 
    }
    print(ans);
    return output(), 0;
}