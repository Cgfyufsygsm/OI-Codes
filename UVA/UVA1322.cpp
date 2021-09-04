#include <cstdio>
#include <cctype>
#include <cstring>
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

const int maxn = 5e4 + 5;

il int min(int a, int b) {return a < b ? a : b;}

int f[maxn << 2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void modify(int i, int j, int k, int x, int v) {
    if (i == j) {
        f[k] = min(f[k], v);
        return;
    }
    if (x <= M) modify(i, M, L, x, v);
    else modify(M + 1, j, R, x, v);
    f[k] = min(f[L], f[R]);
    return;
}

int query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return f[k];
    int ret = 1e9;
    if (x <= M) ret = min(ret, query(i, M, L, x, y));
    if (y > M) ret = min(ret, query(M + 1, j, R, x, y));
    return ret;
}

int n, m;

int main() {
    int T; read(T);
    FOR(kase, 1, T) {
        read(n), read(m);
        memset(f, 0x7f, sizeof f);
        modify(1, n, 1, 1, 0);
        FOR(i, 1, m) {
            int l, r; read(l), read(r);
            modify(1, n, 1, r, query(1, n, 1, l, r) + 1);
        }
        print(query(1, n, 1, n, n)), putchar('\n');
        if (kase < T) putchar('\n');
    }
    return output(), 0;
}