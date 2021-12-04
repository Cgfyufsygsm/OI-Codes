#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)
#define lowbit(x) (x & -x)

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
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
const int maxn = 1e5 + 5, N = 2e4 + 100, delta = 1e4 + 1;
int a[maxn], n, k, s[maxn], tmp[maxn];
ll ans;

void solve(int l, int r) {
    if (l == r) return;
    int mid = (l + r) >> 1;
    solve(l, mid), solve(mid + 1, r);
    int i, j, k = l;
    ll cnt = 0;
    for (i = l, j = mid + 1; j <= r;) {
        while (s[i] <= s[j] && i <= mid) {
            ++cnt;
            tmp[k++] = s[i++];
        }
        ans += cnt;
        tmp[k++] = s[j++];
    }
    while (i <= mid) tmp[k++] = s[i++];
    FOR(i, l, r) s[i] = tmp[i];
    return;
}

int main() {
    read(n, k);
    FOR(i, 1, n) read(a[i]), a[i] -= k, s[i] = s[i - 1] + a[i];
    solve(0, n);
    print(ans);
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}