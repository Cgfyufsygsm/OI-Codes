#include <cstdio>
#include <cctype>
#include <vector>
#include <queue>
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

const int maxn = 2e5 + 5;
int rv[maxn], cv[maxn];
int n, h, w, ans[maxn];

struct node {
    int id, x, y, c;
} a[maxn];

int main() {
    read(h), read(w), read(n);
    FOR(i, 1, n)
        read(a[i].x), read(a[i].y), read(a[i].c), a[i].id = i;
    std::sort(a + 1, a + n + 1, [](const node &a, const node &b) {return a.c > b.c;});
    memset(rv, -1, sizeof rv), memset(cv, -1, sizeof cv);
    std::queue<int> q;
    FOR(i, 1, n) {
        ans[a[i].id] = max(rv[a[i].x], cv[a[i].y]) + 1;
        q.push(i);
        if (i < n && a[i].c != a[i + 1].c) while (!q.empty()) {
            int id = q.front(); q.pop();
            rv[a[id].x] = max(rv[a[id].x], ans[a[id].id]);
            cv[a[id].y] = max(cv[a[id].y], ans[a[id].id]);
        }
    }
    FOR(i, 1, n) print(ans[i], '\n');
    return output(), 0;
}