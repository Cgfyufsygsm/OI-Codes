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

const int maxn = 1e5 + 5;
using ll = long long;
int n;
vector<ll> neg, pos, zero;
using state = pair<bool, ll>;

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        neg.clear(), pos.clear(), zero.clear();
        FOR(i, 1, n) {
            ll x; read(x);
            if (x > 0) pos.push_back(x);
            else if (x < 0) neg.push_back(x);
            else if (x == 0) zero.push_back(x);
        }
        ll ans = -4e18;
        sort(pos.begin(), pos.end(), greater<int>());
        sort(neg.begin(), neg.end());
        state pos_s[6];
        FOR(i, 1, 5) {
            if (pos.size() >= i) {
                pos_s[i].first = 1;
                pos_s[i].second = 1;
                FOR(j, 0, i - 1) pos_s[i].second *= pos[j];
            } else {
                pos_s[i].first = 0;
                pos_s[i].second = 1;
            }
        }
        state neg_abs[6], neg_min[6];
        FOR(i, 1, 5) {
            if (neg.size() >= i) {
                neg_abs[i].first = neg_min[i].first = 1;
                neg_abs[i].second = neg_min[i].second = 1;
                FOR(j, 0, i - 1) neg_abs[i].second *= neg[j];
                DEC(j, (int)neg.size() - 1, (int)neg.size() - i) neg_min[i].second *= neg[j];
            } else {
                neg_abs[i].first = neg_min[i].first = 0;
                neg_abs[i].second = neg_min[i].second = 1;
            }
        }
        if (zero.size()) chkmax(ans, 0ll);
        if (pos_s[5].first) chkmax(ans, pos_s[5].second);//, printf("case 1\n");
        if (pos_s[4].first && neg_min[1].first) chkmax(ans, pos_s[4].second * neg_min[1].second);//, printf("case 2\n");;
        if (pos_s[3].first && neg_abs[2].first) chkmax(ans, pos_s[3].second * neg_abs[2].second);//, printf("case 3\n");;
        if (pos_s[2].first && neg_min[3].first) chkmax(ans, pos_s[2].second * neg_min[3].second);//, printf("case 4\n");;
        if (pos_s[1].first && neg_abs[4].first) chkmax(ans, pos_s[1].second * neg_abs[4].second);//, printf("case 5\n");;
        if (neg_min[5].first) chkmax(ans, neg_min[5].second);//, printf("case 6\n");;
        print(ans);
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}