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

const int maxn = 305;
int n, m;

struct node {
    int a, ord, pos;
} p[maxn];

int t[maxn];

#define lowbit(x) (x & -x)

void add(int x, int v) {
    for (; x <= m; x += lowbit(x)) t[x] += v;
    return;
}

int query(int x) {
    int ret = 0;
    for (; x; x -= lowbit(x)) ret += t[x];
    return ret;
}

il bool cmp1(const node &x, const node &y) {return x.a == y.a ? x.ord > y.ord : x.a < y.a;}
il bool cmp2(const node &x, const node &y) {return x.ord < y.ord;}

int main() {
    int T; read(T);
    while (T--) {
        read(n), read(m);
        FOR(i, 1, n * m) read(p[i].a), p[i].ord = i;
        std::sort(p + 1, p + n * m + 1, cmp1);
        FOR(i, 1, n * m) p[i].pos = i;
        std::sort(p + 1, p + n * m + 1, cmp2);
        int ans = 0;
        FOR(i, 1, n * m) {
            ans += query(p[i].pos);
            add(p[i].pos, 1);
        }
        FOR(i, 1, n * m) add(p[i].pos, -1);
        print(ans), putchar('\n');
    }
    return output(), 0;
}