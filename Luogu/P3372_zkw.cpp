#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = 1e5 + 5;
int n, N, m;
ll t[maxn << 2], tag[maxn << 2];

void modify(int x, int y, ll k) {
    int lNum = 0, rNum = 0, nNum = 1;
    for (x += N - 1, y += N + 1; x ^ y ^ 1; x >>= 1, y >>= 1, nNum <<= 1) {
        t[x] += k * lNum, t[y] += k * rNum;
        if (~x & 1) tag[x ^ 1] += k, t[x ^ 1] += k * nNum, lNum += nNum;
        if (y & 1) tag[y ^ 1] += k, t[y ^ 1] += k * nNum, rNum += nNum;
    }
    for (; x; x >>= 1, y >>= 1) t[x] += k * lNum, t[y] += k * rNum;
    return;
}

ll query(int x, int y) {
    int lNum = 0, rNum = 0, nNum = 1;
    ll ret = 0;
    for (x += N - 1, y += N + 1; x ^ y ^ 1; x >>= 1, y >>= 1, nNum <<= 1) {
        if (tag[x]) ret += lNum * tag[x];
        if (tag[y]) ret += rNum * tag[y];
        if (~x & 1) ret += t[x ^ 1], lNum += nNum;
        if (y & 1) ret += t[y ^ 1], rNum += nNum;
    }
    for (; x; x >>= 1, y >>= 1) ret += tag[x] * lNum + tag[y] * rNum;
    return ret;
}

int main() {
    read(n, m);
    for (N = 1; N <= n + 1; N <<= 1);
    FOR(i, N + 1, N + n) read(t[i]);
    DEC(i, N - 1, 1) t[i] = t[i << 1] + t[i << 1 | 1];
    while (m--) {
        int c, x, y; read(c, x, y);
        if (c == 1) {
            ll k; read(k);
            modify(x, y, k);
        } else print(query(x, y));
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}