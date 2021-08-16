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

const int maxn = 1e3 + 5;
int n, m1, m2;
int fa1[maxn], fa2[maxn];
int ans, ansx[maxn], ansy[maxn];

int find(int *fa, int u) {return u == fa[u] ? u : fa[u] = find(fa, fa[u]);}

void merge(int *fa, int u, int v) {
    u = find(fa, u), v = find(fa, v);
    if (u == v) return;
    fa[v] = u;
    return;
}

int main() {
    read(n), read(m1), read(m2);
    FOR(i, 1, n) fa1[i] = fa2[i] = i;
    FOR(i, 1, m1) {
        int u, v; read(u), read(v);
        merge(fa1, u, v);
    }
    FOR(i, 1, m2) {
        int u, v; read(u), read(v);
        merge(fa2, u, v);
    }
    FOR(i, 1, n) {
        FOR(j, i + 1, n) {
            if (find(fa1, i) != find(fa1, j) && find(fa2, i) != find(fa2, j)) {
                ++ans, ansx[ans] = i, ansy[ans] = j;
                merge(fa1, i, j), merge(fa2, i, j);
            }
        }
    }
    print(ans), putchar('\n');
    FOR(i, 1, ans) print(ansx[i]), putchar(' '), print(ansy[i]), putchar('\n');
    return output(), 0;
}