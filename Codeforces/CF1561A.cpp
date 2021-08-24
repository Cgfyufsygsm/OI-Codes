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

const int maxn = 1005;

il void swap(int &a, int &b) {
    int t = a;
    a = b, b = t;
    return;
}

int a[maxn], n;

il void f(int i) {
    if (a[i] > a[i + 1]) swap(a[i], a[i + 1]);
    return;
}

il bool check() {
    FOR(i, 1, n - 1) if (a[i] > a[i + 1]) return 0;
    return 1;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        int p = 0;
        for (int i = 1; ; ++i) {
            if (check()) break;
            if (i & 1) {
                for (int j = 1; j <= n - 2; j += 2)
                    f(j);
            } else {
                for (int j = 2; j <= n - 1; j += 2)
                    f(j);
            }
            p = i;
        }
        print(p), putchar('\n');
    }
    return output(), 0;
}