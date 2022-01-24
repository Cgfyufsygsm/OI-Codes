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
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
using pil = pair<int, ll>;
const int maxn = 1e5 + 5;
const ll INF = 0x3f3f3f3f3f3f3f3f;
ll x[maxn], dp[maxn];
struct ladder {
    int a, b, c, d, h;
    ladder() {}
    ladder(int _a, int _b, int _c, int _d, int _h) : a(_a), b(_b), c(_c), d(_d), h(_h) {}
};
vector<ladder> lad[maxn];
map<int, ll> row[maxn];

void solve() {
    int n, m, k; read(n, m, k);
    FOR(i, 1, n) read(x[i]), vector<ladder>().swap(lad[i]), map<int, ll>().swap(row[i]);
    FOR(i, 1, k) {
        int a, b, c, d, h; read(a, b, c, d, h);
        lad[a].push_back(ladder(a, b, c, d, h));
        row[a][b] = INF, row[c][d] = INF;
    }
    row[1][1] = 0, row[n][m] = INF;
    FOR(i, 1, n) {
        if (row[i].size() >= 2) {
            pil last = *row[i].begin();
            for (auto it = ++(row[i].begin()); it != row[i].end(); last = *it++)
                chkmin(it->second, last.second + x[i] * myabs(last.first - it->first));
            last = *row[i].rbegin();
            for (auto it = ++(row[i].rbegin()); it != row[i].rend(); last = *it++)
                chkmin(it->second, last.second + x[i] * myabs(last.first - it->first));
        }
        for (auto ld : lad[i])
            if (row[ld.a][ld.b] < INF) chkmin(row[ld.c][ld.d], row[ld.a][ld.b] - ld.h);
    }
    if (row[n][m] < INF) print(row[n][m]);
    else print("NO ESCAPE");
}

int main() {
    int T; read(T);
    while (T--) solve();
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}