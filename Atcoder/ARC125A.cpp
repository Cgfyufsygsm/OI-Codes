#include <cstdio>
#include <cctype>
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

const int maxn = 2e5 + 5;
int n, m, minc;
int s[maxn], t[maxn];

il int min(int a, int b) {return a < b ? a : b;}

int main() {
    read(n), read(m);
    FOR(i, 1, n) read(s[i]);
    FOR(i, 1, m) read(t[i]);
    minc = 1e9;
    FOR(i, 1, n) if (s[i] != s[1]) minc = min(minc, min(i - 1, n - i + 1));
    int ans = 0;
    if (minc == 1e9) {
        int flag = 1;
        FOR(i, 1, m) if (t[i] != s[1]) {flag = 0; break;}
        if (!flag) return print(-1), output(), 0;
    }
    int p = 1, fir = 1;
    while (p <= m) {
        if (p <= m && t[p] == s[1]) {
            if (p != 1) ++ans;
            while (p <= m && t[p] == s[1])
                ++ans, ++p;
        }
        if (p <= m && t[p] != s[1]) {
            if (fir) ans += minc, fir = 0;
            else if (p != 1) ++ans;
            while (p <= m && t[p] != s[1])
                ++ans, ++p;
        }
    }
    print(ans);
    return output(), 0;
}