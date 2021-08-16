#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int maxn = 200000 + 5;

int n, s[maxn], t[maxn], ans[maxn];

il int min(int a, int b) {return a < b ? a : b;}

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

int main() {
    read(n);
    FOR(i, 1, n) read(s[i]);
    FOR(i, 1, n) read(t[i]);
    int st, mint = 2e9;
    FOR(i, 1, n) if (mint > t[i]) mint = t[i], st = i;
    ans[st] = t[st];
    for (int i = st; i <= st + n - 1; ++i) {
        int now = i > n ? i - n : i;
        int nxt = now + 1;
        if (nxt > n) nxt -= n;
        ans[nxt] = min(t[nxt], ans[now] + s[now]);
    }
    FOR(i, 1, n) print(ans[i]), putchar('\n');
    return output(), 0;
}