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

const int maxn = 1e7 + 5;
int n, a[maxn], ls[maxn], rs[maxn], stk[maxn], top;
ll ans1, ans2;

int main() {
    read(n);
    FOR(i, 1, n) read(a[i]);
    stk[top = 1] = 1;
    FOR(i, 2, n) {
        while (a[stk[top]] > a[i] && top) --top;
        if (!top) ls[i] = stk[top + 1];
        else ls[i] = rs[stk[top]], rs[stk[top]] = i;
        stk[++top] = i;
    }
    FOR(i, 1, n) {
        ans1 ^= (1ll * i * (ls[i] + 1));
        ans2 ^= (1ll * i * (rs[i] + 1));
    }
    print(ans1), putchar(' '), print(ans2);
    return output(), 0;
}