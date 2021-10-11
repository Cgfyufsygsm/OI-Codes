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
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e3 + 5;
int a[maxn][6], n;

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) FOR(j, 1, 5) read(a[i][j]);
        bool flag0 = 0;
        FOR(i, 1, 5) {
            FOR(j, i + 1, 5) {
                int n1 = 0, n2 = 0, n3 = 0;
                bool flag = 1;
                FOR(k, 1, n) {
                    if (a[k][i] && a[k][j]) ++n3;
                    else if (a[k][i]) ++n1;
                    else if (a[k][j]) ++n2;
                    else {
                        flag = 0;
                        break;
                    }
                }
                if (!flag) continue;
                if (n1 > n2) myswap(n1, n2);
                if (n1 < n / 2) n3 -= n / 2 - n1;
                if (n2 < n / 2) n3 -= n / 2 - n2;
                if (n3 >= 0) flag0 = 1;
            }
        }
        puts(flag0 ? "YES" : "NO");
    }
    return output(), 0;
}