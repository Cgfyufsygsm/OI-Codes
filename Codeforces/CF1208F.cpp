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

const int maxn = 1 << 21 | 500;
int n, a[maxn], fi[maxn], se[maxn];

void add(int msk, int pos) {
    if (pos > fi[msk]) {
        se[msk] = fi[msk];
        fi[msk] = pos;
    } else if (pos > se[msk] && pos != fi[msk])
        se[msk] = pos;
    return;
}

il void merge(int msk1, int msk2) {
    add(msk1, fi[msk2]);
    add(msk1, se[msk2]);
    return;
}

il int max(const int &a, const int &b) {return a > b ? a : b;}

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]), add(a[i], i);
    FOR(j, 0, 21)
        FOR(i, 0, (1 << 21) - 1)
            if ((i >> j) & 1) merge(i ^ (1 << j), i);
    int ans = 0;
    FOR(i, 1, n - 2) {
        int res = 0;
        DEC(j, 21, 0) {
            if (a[i] & (1 << j)) continue;
            if (se[res | (1 << j)] > i) {
                res |= (1 << j);
            }
        }
        ans = max(ans, res | a[i]);
    }
    print(ans);
    return output(), 0;
}