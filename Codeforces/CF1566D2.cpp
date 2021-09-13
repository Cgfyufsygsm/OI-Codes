#include <cstdio>
#include <cctype>
#include <queue>
#include <utility>
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

int main() {
    int T; read(T);
    while (T--) {
        int n, m;
        read(n), read(m);
        std::vector<std::pair<int, int> > a(n * m);
        FOR(i, 0, n * m - 1) read(a[i].first), a[i].second = i;
        std::sort(a.begin(), a.end());
        FOR(i, 0, n * m - 1) a[i].second = -a[i].second;
        int ans = 0;
        FOR(i, 0, n - 1) {
            std::sort(a.begin() + (m * i), a.begin() + (m * (i + 1)));
            FOR(j, 0, m - 1) {
                FOR(k, 0, j - 1) {
                    if (a[m * i + k].second > a[m * i + j].second)
                        ++ans;
                }
            }
        }
        print(ans), putchar('\n');
    }
    return output(), 0;
}