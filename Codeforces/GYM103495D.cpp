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

using pii = pair<int, int>;
vector<pii> ans;
int n, m;

vector<pii> calc() {
    vector<pii> ret;
    ret.push_back({1, 1});
    ret.push_back({3, 2});
    ret.push_back({1, 3});
    ret.push_back({2, 1});
    ret.push_back({3, 3});
    ret.push_back({1, 2});
    ret.push_back({3, 1});
    ret.push_back({2, 3});
    ret.push_back({2, 2});
    for (int i = 4; i <= n; i += 2) {
        ret.push_back({i + 1, 3});
        ret.push_back({i, 3});
        ret.push_back({i + 1, 2});
        ret.push_back({i, 2});
        ret.push_back({i + 1, 1});
        ret.push_back({i, 1});
    }
    return ret;
}

int main() {
    read(n, m);
    bool flg = 0;
    if ((m & 1) && !(n & 1)) swap(n, m), flg = 1;
    if (n == 2) swap(n, m), flg = 1;
    FOR(j, 1, (m & 1) ? m / 2 - 1 : m / 2) {
        if (j & 1) {
            ans.push_back({n, 2 * j - 1});
            DEC(i, n - 1, 1) {
                ans.push_back({i, 2 * j});
                ans.push_back({i, 2 * j - 1});
            }
            ans.push_back({n, 2 * j});
        } else {
            ans.push_back({1, 2 * j - 1});
            FOR(i, 2, n) {
                ans.push_back({i, 2 * j});
                ans.push_back({i, 2 * j - 1});
            }
            ans.push_back({1, 2 * j});
        }
    }
    if (m & 1) {
        vector<pii> tmp = calc();
        for (auto &p : tmp) {
            if (m % 4 == 3) p.first = n - p.first + 1;
            p.second += m - 3;
            ans.push_back(p);
        }
    }
    for (auto &p : ans) {
        if (!flg) print(p.first, p.second);
        else print(p.second, p.first);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}