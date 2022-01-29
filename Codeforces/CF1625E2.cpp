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
const int maxn = 3e5 + 5;
char s[maxn];
int n, q;

struct bit {
    vector<ll> s; int sz;
    void build(int SZ) {sz = SZ + 5, s.resize(sz); return;}
    void add(int x, ll v) {for (; x < sz; x += (x & -x)) s[x] += v; return;}
    ll query(int x) {ll ret = 0; for (; x; x -= (x & -x)) ret += s[x]; return ret;}
} T, t[maxn];

int son[maxn], fa[maxn], bel[maxn], ord[maxn], size[maxn];

int main() {
    read(n, q);
    read(s + 1);
    int cnt = 1, now = 1;
    FOR(i, 1, n) {
        if (s[i] == '(') {
            ord[++cnt] = ++son[now];
            fa[cnt] = now, bel[i] = cnt, now = cnt;
        } else if (now != 1) {
            bel[i] = now;
            now = fa[now];
        }
    }
    T.build(cnt);
    FOR(i, 1, cnt) {
        T.add(i, 1ll * son[i] * (son[i] + 1) / 2);
        t[i].build(son[i]);
    }
    DEC(i, cnt, 1) size[fa[i]] += (++size[i]);
    while (q--) {
        int op, l, r; read(op, l, r);
        if (op == 1) {
            int now = bel[l];
            t[fa[now]].add(ord[now], 1);
            T.add(fa[now], -son[fa[now]]--);
        } else {
            l = bel[l], r = bel[r];
            ll ans = T.query(r + size[r] - 1) - T.query(l - 1);
            ll cnt = ord[r] - ord[l] + 1 - t[fa[l]].query(ord[r]) + t[fa[l]].query(ord[l] - 1);
            ans += cnt * (cnt + 1) / 2;
            print(ans);
        }
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}