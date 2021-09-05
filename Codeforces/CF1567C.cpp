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

typedef long long ll;

ll f[11][2][2];//f[i][j] 从低到高第 i 位，该位和上一位有无进位方案数
int a[11];

const int trans[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 9, 8, 7, 6, 5, 4, 3, 2, 1};

int main() {
    int T; read(T);
    while (T--) {
        int n; read(n);
        int len = 0;
        while (n) a[++len] = n % 10, n /= 10;
        f[1][0][0] = trans[a[1]];
        f[1][1][0] = trans[a[1] + 10];
        FOR(i, 2, len) {
            f[i][0][0] = trans[a[i]] * f[i - 1][0][0];
            if (a[i]) f[i][0][0] += trans[a[i] - 1] * f[i - 1][0][1];
            f[i][0][1] = trans[a[i]] * f[i - 1][1][0];
            if (a[i]) f[i][0][1] += trans[a[i] - 1] * f[i - 1][1][1];
            f[i][1][0] = trans[a[i] + 10] * f[i - 1][0][0] + trans[a[i] + 9] * f[i - 1][0][1];
            f[i][1][1] = trans[a[i] + 10] * f[i - 1][1][0] + trans[a[i] + 9] * f[i - 1][1][1];
        }
        print(f[len][0][0] - 2);putchar('\n');
    }
    return output(), 0;
}