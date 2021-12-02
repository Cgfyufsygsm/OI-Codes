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

struct node {
    int id, t;
    node(int i, int _t) : id(i), t(_t) {}
    friend il bool operator<(const node &a, const node &b) {return a.t < b.t;}
    friend il bool operator==(const node &a, const node &b) {return a.id == b.id && a.t == b.t;}
};

const int maxn = 1e5 + 5;
int a[3][maxn], b[3][maxn], n, m1, m2, f[maxn], g[maxn];
std::set<node> s1, s2;

void solve(int *a, int *b, int m, int *f) {
    s1.clear(), s2.clear();
    FOR(i, 1, m) s1.insert(node(i, a[i])), s2.insert(node(i, b[i]));
    FOR(i, 1, n) {
        f[i] = f[i - 1];
        int now = 0;
        std::set<node>::iterator it;
        while ((it = s1.lower_bound(node(1, now))) != s1.end()) {
            ++f[i];
            int id = it->id;
            now = b[id];
            s1.erase(node(id, a[id])), s2.erase(node(id, b[id]));
        }
    }
    return;
}

int main() {
    read(n), read(m1), read(m2);
    FOR(i, 1, m1) read(a[1][i]), read(b[1][i]);
    FOR(i, 1, m2) read(a[2][i]), read(b[2][i]);
    solve(a[1], b[1], m1, f);
    solve(a[2], b[2], m2, g);
    int ans = 0;
    FOR(i, 0, n) chkmax(ans, f[i] + g[n - i]);
    print(ans, '\n');
    return output(), 0;
}