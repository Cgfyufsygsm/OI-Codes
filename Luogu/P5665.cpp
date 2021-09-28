#include <cstdio>
#include <cctype>
#include <cstring>
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

using int128 = __int128;
using ll = long long;
using uint = unsigned int;
const int maxn = 4e7 + 5;
int n, m, g[maxn], q[maxn], head, tail;
ll s[maxn];
uint b[maxn], x, y, z;

void gen() {
    static const uint msk = (1ll << 30) - 1;
    read(x), read(y), read(z), read(b[1]), read(b[2]), read(m);
    FOR(i, 3, n) b[i] = (x * b[i - 1] + y * b[i - 2] + z) & msk;
    int i = 1;
    FOR(j, 1, m) {
        int p, l, r; read(p), read(l), read(r);
        for (; i <= p; ++i) s[i] = s[i - 1] + b[i] % (r - l + 1) + l;
    }
    return;
}

il ll w(int i) {return 2 * s[i] - s[g[i]];}

int main() {
    read(n);
    int type; read(type);
    if (!type) FOR(i, 1, n) read(s[i]), s[i] += s[i - 1];
    else gen();
    q[head = tail = 1] = 0;
    FOR(i, 1, n) {
        while (head < tail && w(q[head + 1]) <= s[i]) ++head;
        g[i] = q[head];
        while (head <= tail && w(q[tail]) >= w(i)) --tail;
        q[++tail] = i;
    }
    int128 ans = 0, one = 1;
    for (int now = n; now; now = g[now]) ans += one * (s[now] - s[g[now]]) * (s[now] - s[g[now]]);
    print(ans);
    return output(), 0;
}