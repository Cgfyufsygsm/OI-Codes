#include <cstdio>
#include <cctype>
#include <cassert>
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

int T, p;
int n, n1, n2, m;
int a[17];

int qPow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % p)
        if (b & 1) ret = 1ll * ret * a % p;
    return ret;
}

namespace p10007 {
    using namespace std;
    const int mod = 10007;
    int fac[10050], invfac[10050];

    void init() {
        fac[0] = 1;
        FOR(i, 1, mod - 1) fac[i] = 1ll * fac[i - 1] * i % mod;
        invfac[mod - 1] = qPow(fac[mod - 1], mod - 2, mod);
        DEC(i, mod - 2, 0) invfac[i] = 1ll * invfac[i + 1] * (i + 1) % mod;
        return;
    }

    il int C(int n, int m, int p) {
        if (n < m) return 0;
        if (!m) return 1;
        return 1ll * fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    }

    int lucas(int n, int m, int p) {
        if (!m) return 1;
        return 1ll * lucas(n / p, m / p, p) * C(n % p, m % p, p) % p;
    }
}

void exgcd(int a, int b, int &x, int &y) {
    if (!b) {
        x = 1, y = 0;
        return;
    }
    exgcd(b, a % b, y, x);
    y -= a / b * x;
    return;
}

il int inv(int n, int p) {
    int x, y;
    exgcd(n, p, x, y);
    return (x + p) % p;
}

int q1[] = {0, 2, 3, 11, 397, 10007}, q2[] = {0, 5, 7, 101}, q[10];
int qk1[] = {0, 2, 3, 11, 397, 10007}, qk2[] = {0, 125, 343, 10201}, qk[10], d;
int retfac[10];

int calc(int n, int i) {
    if (!n) return 1;
    int ret = retfac[i];
    ret = qPow(ret, n / qk[i], qk[i]);
    FOR(j, n / qk[i] * qk[i] + 1, n)
        if (j % q[i]) ret = 1ll * ret * (j % qk[i]) % qk[i];
    return 1ll * ret * calc(n / q[i], i) % qk[i];
}

int multiLucas(int n, int m, int i) {
    if (n < m) return 0;
    int cnt = 0;
    for (int j = n; j; j /= q[i]) cnt += j / q[i];
    for (int j = m; j; j /= q[i]) cnt -= j / q[i];
    for (int j = n - m; j; j /= q[i]) cnt -= j / q[i];
    return 1ll * qPow(q[i], cnt, qk[i]) * calc(n, i) % qk[i] * inv(calc(m, i), qk[i]) % qk[i] * inv(calc(n - m, i), qk[i]) % qk[i];
}

int CRT(int n, int *a, int *m, int mod) {
    int M = 1, ret = 0;
    FOR(i, 1, n) M *= m[i];
    FOR(i, 1, n) {
        int w = M / m[i];
        ret = (ret + 1ll * a[i] * w % mod * inv(w, m[i]) % mod) % mod;
    }
    return (ret + mod) % mod;
}

int exLucas(int n, int m, int p) {
    if (n < m) return 0;
    if (p == 10007) return p10007::lucas(n, m, p);
    int a[10];
    FOR(i, 1, d) a[i] = multiLucas(n, m, i);
    return CRT(d, a, qk, p);
}

void init() {
    if (p == 262203414) {
        d = 5;
        FOR(i, 1, d) qk[i] = qk1[i], q[i] = q1[i];
    } else {
        d = 3;
        FOR(i, 1, d) qk[i] = qk2[i], q[i] = q2[i];
    }
    FOR(i, 1, d) {
        retfac[i] = 1;
        FOR(j, 1, qk[i])
            if (j % q[i]) retfac[i] = 1ll * retfac[i] * j % qk[i];
    }
    return;
}

int main() {
    read(T), read(p);
    p10007::init();
    init();
    while (T--) {
        read(n), read(n1), read(n2), read(m);
        FOR(i, 1, n1 + n2) read(a[i]);
        FOR(i, n1 + 1, n1 + n2) m -= a[i] - 1;
        int ans = 0;
        FOR(S, 0, (1 << n1) - 1) {
            int popcnt = 0, nowm = m;
            FOR(i, 1, n1)
                if ((1 << (i - 1)) & S) nowm -= a[i], ++popcnt;
            int tmp = exLucas(nowm - 1, n - 1, p);
            ans = (ans + ((popcnt & 1) ? (p - tmp + p) % p : tmp)) % p;
        }
        print(ans), putchar('\n');
    }
    return output(), 0;
}
