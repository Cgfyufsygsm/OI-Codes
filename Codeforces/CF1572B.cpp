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
void print(const char *s) {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

const int maxn = 2e5 + 5;
int n, a[maxn], sum[maxn];

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]), sum[i] = sum[i - 1] ^ a[i];
        if (sum[n]) {
            print("NO\n");
            continue;
        } else {
            if (n & 1) {
                print("YES\n");
                print(n - 1, '\n');
                for (int i = n - 2; i >= 1; i -= 2) print(i, ' ');
                for (int i = 1; i <= n - 2; i += 2) print(i, i == n - 2 ? '\n' : ' ');
            } else {
                int p, flag = 0;
                for (p = 1; p < n; p += 2) if (!sum[p]) {flag = 1; break;}
                if (!flag) print("NO\n");
                else {
                    print("YES\n");
                    print(n - 2, '\n');
                    for (int i = p - 2; i >= 1; i -= 2) print(i, ' ');
                    for (int i = 1; i <= p - 2; i += 2) print(i, ' ');
                    for (int i = n - 2; i > p; i -= 2) print(i, ' ');
                    for (int i = p + 1; i <= n - 2; i += 2) print(i, i == n - 2 ? '\n' : ' ');
                }
            }
        }
    }
    return output(), 0;
}