#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 21;
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

const int maxn = 2e5 + 5;
int n, m, oud[maxn], cnt;

il void swap(int &a, int &b) {
    int t = a; a = b; b = t;
    return;
}

int main() {
    read(n), read(m);
    FOR(i, 1, m) {
        int u, v; read(u), read(v);
        u < v ? ++oud[u] : ++oud[v];
    }
    FOR(i, 1, n) cnt += (!oud[i]);
    int q;
    read(q);
    while (q--) {
        int op; read(op);
        if (op == 1) {
            int u, v; read(u), read(v);
            if (u > v) swap(u, v);
            if (!oud[u]++) --cnt;
        } else if (op == 2) {
            int u, v; read(u), read(v);
            if (u > v) swap(u, v);
            if (!--oud[u]) ++cnt;
        } else print(cnt), putchar('\n');
    }
    return output(), 0;
}