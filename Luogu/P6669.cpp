#include <cstdio>
#include <cctype>
#include <cstring>
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
const ll mod = 1e9 + 7;
ll t, k, n, m, bn[66], bm[66];
ll f[66][2][2][2][2];

ll solve(int cur, bool ok, bool dif, bool fn, bool fm) {
    if (!cur) return ok;
    ll &res = f[cur][ok][dif][fn][fm];
    if (~res) return res;
    res = 0;
    int upn = fn ? k - 1 : bn[cur], upm = fm ? k - 1 : bm[cur];
    FOR(i, 0, upn)
        for (int j = 0; (j <= i || dif) && j <= upm; ++j)
            res = (res + solve(cur - 1, ok | (i < j), dif | (i != j), fn | (i < upn), fm | (j < upm))) % mod;
    return res;
}

int main() {
    read(t), read(k);
    while (t--) {
        read(n), read(m);
        ll mx = n > m ? n : m, len = 0;
        memset(f, -1, sizeof f);
        while (mx) mx /= k, ++len;
        FOR(i, 1, len) bn[i] = n % k, n /= k;
        FOR(i, 1, len) bm[i] = m % k, m /= k;
        print(solve(len, 0, 0, 0, 0)), putchar('\n');
    }
    return output(), 0;
}