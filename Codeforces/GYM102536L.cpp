#include <cstdio>
#include <cctype>
#include <cstring>
#include <cassert>
#include <set>
#include <algorithm>
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

const int mod = 999983;

int n, k, l;

struct poly {
    int d;
    int f[105];
    poly() {d = 0; memset(f, 0, sizeof f);}
    void out() {
        print(d), putchar(' ');
        DEC(i, d, 0) print(f[i]), putchar(' ');
        putchar('\n');
    }
};

void mul(poly &a, poly &b) {
    int f[105];
    memset(f, 0, sizeof f);
    FOR(i, 0, a.d)
        FOR(j, 0, b.d)
            f[i + j] = (f[i + j] + 1ll * a.f[i] * b.f[j] % mod) % mod;
    a.d += b.d;
    memcpy(a.f, f, sizeof f);
    return;
}

il int min(int a, int b) {return a < b ? a : b;}

int s[55];

int main() {
    int t; read(t);
    while (t--) {
        read(n), read(k), read(l);
        bool vis[205];
        memset(vis, 0, sizeof vis);
        FOR(i, 1, l) {
            read(s[i]);
            s[i] = (s[i] + mod) % mod;
            if (s[i] <= 200) vis[s[i]] = 1;
        }
        std::sort(s + 1, s + l + 1);
        l = std::unique(s + 1, s + l + 1) - s - 1;
        if (k < l) {
            print(0), putchar('\n');
            continue;
        }
        poly ans, tmp;
        ans.d = 1, ans.f[0] = (mod - s[1]) % mod, ans.f[1] = 1;
        FOR(i, 2, l) {
            tmp.d = 1, tmp.f[0] = (mod - s[i]) % mod, tmp.f[1] = 1;
            mul(ans, tmp);
        }
        print(n), putchar('\n');
        FOR(i, 1, n) {
            print(ans.d), putchar(' ');
            DEC(j, ans.d, 0) print(1ll * ans.f[j] * i % mod), putchar(' ');
            putchar('\n');
        }
    }
    return output(), 0;
}