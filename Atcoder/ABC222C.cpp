#include <cstdio>
#include <cctype>
#include <cstring>
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

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 505;
int n, m;
char s[maxn][maxn];

struct node {
    int id, win;
    il bool operator<(const node &b) {return win == b.win ? id > b.id : win < b.win;}
} a[maxn];

int main() {
    scanf("%d %d", &n, &m);
    n <<= 1;
    FOR(i, 1, n) scanf("%s", s[i] + 1), a[i].id = i;
    FOR(i, 1, m) {
        std::sort(a + 1, a + n + 1);
        for (int u = 1, v = 2; v <= n; u += 2, v += 2) {
            if (s[a[u].id][i] == 'G' && s[a[v].id][i] == 'C') ++a[u].win;
            if (s[a[u].id][i] == 'C' && s[a[v].id][i] == 'G') ++a[v].win;
            if (s[a[u].id][i] == 'C' && s[a[v].id][i] == 'P') ++a[u].win;
            if (s[a[u].id][i] == 'P' && s[a[v].id][i] == 'C') ++a[v].win;
            if (s[a[u].id][i] == 'P' && s[a[v].id][i] == 'G') ++a[u].win;
            if (s[a[u].id][i] == 'G' && s[a[v].id][i] == 'P') ++a[v].win;
        }
    }
    std::sort(a + 1, a + n + 1);
    DEC(i, n, 1) print(a[i].id, '\n');
    return output(), 0;
}