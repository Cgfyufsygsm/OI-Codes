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

const int maxn = 1e4 + 5;
int a[maxn], n;

struct node {
    int i, j, x;
    node(int _i = 0, int _j = 0, int _x = 0) : i(_i), j(_j), x(_x) {}
} q[maxn * 3];
int cnt = 0;

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]);
        cnt = 0;
        FOR(i, 2, n) {
            if (a[i] % i) {
                q[++cnt] = node(1, i, i - a[i] % i);
                q[++cnt] = node(i, 1, a[i] / i + 1);
                a[1] += a[i];
                a[i] = 0;
            } else {
                q[++cnt] = node(i, 1, a[i] / i);
                a[1] += a[i];
                a[i] = 0;
            }
        }
        if (a[1] % n) print(-1, '\n');
        else {
            a[1] /= n;
            FOR(i, 2, n) {
                q[++cnt] = node(1, i, a[1]);
                a[i] = a[1];
            }
            print(cnt, '\n');
            FOR(i, 1, cnt) print(q[i].i, ' '), print(q[i].j, ' '), print(q[i].x, '\n');
        }
    }
    return output(), 0;
}