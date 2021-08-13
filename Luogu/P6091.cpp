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

const int maxn = 1e6 + 5;
int isp[maxn], p[maxn], totp, phi[maxn];
int exist[maxn];

void init() {
    const int N = 1e6;
    phi[1] = 1;
    FOR(i, 2, N) {
        if (!isp[i]) p[++totp] = i, phi[i] = i - 1;
        for (int j = 1; j <= totp && i * p[j] <= N; ++j) {
            isp[i * p[j]] = 1;
            if (i % p[j] == 0) {
                phi[i * p[j]] = phi[i] * p[j];
                break;
            }
            phi[i * p[j]] = phi[i] * (p[j] - 1);
        }
    }
    exist[2] = exist[4] = 1;
    FOR(i, 2, totp) {
        for (int j = 1; 1ll * j * p[i] <= N; j *= p[i]) exist[j * p[i]] = 1;
        for (int j = 2; 1ll * j * p[i] <= N; j *= p[i]) exist[j * p[i]] = 1;
    }
    return;
}

int qPow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % p)
        if (b & 1) ret = 1ll * ret * a % p;
    return ret;
}

int fact[maxn], cnt, ans[maxn];

void getFact(int n) {
    int tmp = n;
    for (int j = 1; j <= totp && 1ll * p[j] * p[j] <= n; ++j) {
        if (n % p[j] == 0) {
            while (n % p[j] == 0) n /= p[j];
            fact[++cnt] = tmp / p[j];
        }
    }
    if (n > 1) fact[++cnt] = tmp / n;
    return;
}

bool check(int n, int mod) {
    FOR(i, 1, cnt)
        if (qPow(n, fact[i], mod) == 1)
            return 0;
    return 1;
}

il int gcd(int a, int b) {return !b ? a : gcd(b, a % b);}

int main() {
    init();
    int T; read(T);
    while (T--) {
        int n, d; read(n), read(d);
        if (!exist[n])
            putchar('0'), putchar('\n'), putchar('\n');
        else if (n == 2) {
            putchar('1'), putchar('\n');
            if (d == 1) putchar('1');
            putchar('\n');
        } else {
            int g;
            cnt = 0;
            getFact(phi[n]);
            FOR(m, 1, n) {
                if (gcd(m, n) == 1 && check(m, n)) {
                    g = m;
                    break;
                }
            }
            cnt = 0;
            FOR(i, 1, phi[n] - 1)
                if (gcd(i, phi[n]) == 1)
                    ans[++cnt] = qPow(g, i, n);
            std::sort(ans + 1, ans + cnt + 1);
            print(cnt), putchar('\n');
            for (int i = d; i <= cnt; i += d) print(ans[i]), putchar(' ');
            putchar('\n');
        }
    }
    return output(), 0;
}