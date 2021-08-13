#include <cstdio>
#include <cctype>
#include <ctime>
#include <cstdlib>
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
    il void puts(char *s) {
        for (int i = 0; s[i]; ++i)
            *__pO++ = s[i];
        *__pO++ = '\n';
    }
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

#define puts fastIO::puts
#define putchar fastIO::putchar
#define getchar fastIO::getchar
using namespace fastIO;

il int min(int a, int b) {return a < b ? a : b;}
il int max(int a, int b) {return a > b ? a : b;}

int t, n, p, w;

struct cmplx {
    int x, y;
};

il cmplx mul(cmplx a, cmplx b, int p) {
    cmplx ans = {0, 0};
    ans.x = ((1ll * a.x * b.x % p + 1ll * a.y * b.y % p * w % p) + p) % p;
    ans.y = ((1ll * a.x * b.y % p + 1ll * a.y * b.x % p) + p) % p;
    return ans;
}

int qPow(int a, int b, int p) {
    int ret = 1;
    for (; b; b >>= 1, a = 1ll * a * a % p)
        if (b & 1) ret = 1ll * ret * a % p;
    return ret;
}

int qPow(cmplx a, int b, int p) {
    cmplx ans = {1, 0};
    for (; b; b >>= 1, a = mul(a, a, p))
        if (b & 1) ans = mul(ans, a, p);
    return ans.x % p;
}

int cipolla(int n, int p) {
    n %= p;
    if (p == 2) return n;
    if (qPow(n, (p - 1) / 2, p) == p - 1) return -1;
    int a;
    while (1) {
        a = rand() % p;
        w = ((1ll * a * a % p - n) % p + p) % p;
        if (qPow(w, (p - 1) / 2, p) == p - 1) break;
    }
    cmplx x = {a, 1};
    return qPow(x, (p + 1) / 2, p);
}

int main() {
    srand(time(0));
    read(t);
    while (t--) {
        read(n), read(p);
        if (!n) {
            putchar('0'), putchar('\n');
            continue;
        }
        int ans1 = cipolla(n, p), ans2 = p - ans1;
        if (ans1 == -1) {
            puts("Hola!");
            continue;
        }
        else print(min(ans1, ans2)), putchar(' '), print(max(ans1, ans2));
        putchar('\n');
    }
    return output(), 0;
}