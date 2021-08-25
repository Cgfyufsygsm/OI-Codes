#include <cstdio>
#include <cctype>
#include <set>
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

int a, b;

il int min(int a, int b) {return a < b ? a : b;}

int main() {
    int T; read(T);
    while (T--) {
        read(a), read(b);
        std::set<int> ans;
        if ((a + b) & 1) {
            int n1 = (a + b) >> 1;
            int n2 = a + b - n1;
            FOR(i, 0, min(n1, b))
                if (n2 - b + i >= 0) ans.insert(i + n2 - b + i);
            FOR(i, 0, min(n2, b))
                if (n1 - b + i >= 0) ans.insert(i + n1 - b + i);
        } else {
            int n = (a + b) >> 1;
            FOR(i, 0, min(n, b))
                if (n - b + i >= 0) ans.insert(i + n - b + i);
        }
        print(ans.size()), putchar('\n');
        for (auto i : ans) print(i), putchar(' ');
        putchar('\n');
    }
    return output(), 0;
}