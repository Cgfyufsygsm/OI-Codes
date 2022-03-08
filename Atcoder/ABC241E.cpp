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

const int maxn = 2e5 + 5;
using ll = long long;
ll k, a[maxn];
int n, loopS;
bool vis[maxn];

int dfs(int now) {
    if (vis[now]) return now;
    vis[now] = 1;
    return dfs((now + a[now]) % n);
}

void dfs(int now, int &len, ll &val) {
    if (now == loopS && len != 0) return;
    ++len, val += a[now];
    dfs((now + a[now]) % n, len, val);
    return;
}

ll calc0(int now, int step) {
    if (step == k) return 0;
    return calc0((now + a[now]) % n, step + 1) + a[now];
}

int main() {
    read(n, k);
    FOR(i, 0, n - 1) read(a[i]);
    loopS = dfs(0);
    //printf("loop %d\n", loopS);
    int loopLen = 0;
    ll loopVal = 0;
    dfs(loopS, loopLen, loopVal);
    //printf("looplen %d\n", loopLen);
    int stLen = 0;
    ll stVal = 0;
    dfs(0, stLen, stVal);
    //printf("stlen %d stval %lld\n", stLen, stVal);
    if (k < stLen) print(calc0(0, 0));
    else {
        k -= stLen;
        ll ans = stVal + loopVal * (k / loopLen);
        k %= loopLen;
        ans += calc0(loopS, 0);
        print(ans);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}