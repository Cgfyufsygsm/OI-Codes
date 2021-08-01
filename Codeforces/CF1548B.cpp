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

typedef long long ll;
const int maxn = 2e5 + 5;

il ll gcd(ll a, ll b) {return !b ? a : gcd(b, a % b);}
il ll myabs(ll x) {return x >= 0 ? x : -x;}
il ll max(ll a, ll b) {return a > b ? a : b;}

ll a[maxn], n, g[maxn][20];

int main() {
    int t; read(t);
    while (t--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        if (n == 1) {
            print(1), putchar('\n');
            continue;
        }
        FOR(i, 1, n - 1) g[i][0] = myabs(a[i + 1] - a[i]);
        FOR(j, 1, 18) {
            FOR(i, 1, n - 1) {
                if (i + (1 << (j - 1)) >= n) g[i][j] = g[i][j - 1];
                else g[i][j] = gcd(g[i][j - 1], g[i + (1 << (j - 1))][j - 1]);
            }
        }
        int ans = 1;
        FOR(i, 1, n - 1) {
            ll G = 0, D = 0, d;
            DEC(j, 18, 0) {
                if (i + D + (1 << j) - 1 >= n) continue;
                if ((d = gcd(G, g[i + D][j])) != 1) D += (1 << j), G = d;
            }
            ans = max(ans, D + 1);
        }
        print(ans), putchar('\n');
    }
    return output(), 0;
}