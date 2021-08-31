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

il int max(const int &a, const int &b) {return a > b ? a : b;}

const int maxn = 1 << 18 | 500;
int n, a[maxn], fi[maxn], se[maxn];

void update(int pos, int val) {
    if (val > fi[pos]) {
        se[pos] = fi[pos];
        fi[pos] = val;
    } else if (val > se[pos]) {
        se[pos] = val;
    }
    return;
}

int main() {
    read(n);
    FOR(i, 0, (1 << n) - 1) read(a[i]), fi[i] = a[i], se[i] = -1e9;
    FOR(i, 0, n - 1) {
        FOR(j, 0, (1 << n) - 1) {
            if ((1 << i) & j) {
                update(j, fi[j ^ (1 << i)]);
                update(j, se[j ^ (1 << i)]);
            }
        }
    }
    int ans = 0;
    FOR(i, 1, (1 << n) - 1) ans = max(ans, fi[i] + se[i]), print(ans), putchar('\n');
    return output(), 0;
}