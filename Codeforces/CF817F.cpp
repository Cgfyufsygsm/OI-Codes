#include <cstdio>
#include <cctype>
#include <set>
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
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;

struct node {
    ll l, r;
    mutable bool val;
    node(ll _l, ll _r = 1e18, bool _rev = 0) : l(_l), r(_r), val(_rev) {}
    il friend bool operator<(const node &a, const node &b) {return a.l < b.l;}
};
std::set<node> S;
using IT = std::set<node>::iterator;

IT split(ll pos) {
    auto it = S.lower_bound(node(pos));
    if (it != S.end() && it->l == pos) return it;
    --it;
    if (it->r < pos) return S.end();
    ll l = it->l, r = it->r;
    bool val = it->val;
    S.erase(it);
    S.insert(node(l, pos - 1, val));
    return S.insert(node(pos, r, val)).first;
}

void assign(ll l, ll r, bool val) {
    auto itr = split(r + 1), itl = split(l);
    S.erase(itl, itr);
    S.insert(node(l, r, val));
    return;
}

void reverse(ll l, ll r) {
    auto itr = split(r + 1), itl = split(l);
    for (auto it = itl; it != itr; ++it) it->val ^= 1;
    return;
}

ll query() {
    for (auto i : S) if (i.val == 0) return i.l;
    return (ll)1e18 + 1;
}

int main() {
    int n; read(n);
    S.insert(node(1, 1e18, 0));
    while (n--) {
        int op; read(op);
        ll l, r; read(l), read(r);
        if (op == 1) assign(l, r, 1);
        else if (op == 2) assign(l, r, 0);
        else reverse(l, r);
        print(query(), '\n');
    }
    return output(), 0;
}