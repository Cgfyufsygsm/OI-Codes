#include <cstdio>
#include <cctype>
#include <utility>
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
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

using ll = long long;
using pii = std::pair<ll, ll>;

const int maxn = 205;
ll x[maxn], y[maxn];
int n, k;
pii f[maxn][maxn];

ll S(int i, int j, int k) {return (x[j] - x[i]) * (y[k] - y[i]) - (y[j] - y[i]) * (x[k] - x[i]);}

bool check(ll mid) {
    FOR(len, 3, n) {
        for (int i = 1, j = i + len - 1; j <= n; ++i, ++j) {
            f[i][j] = pii(0, 0);
            FOR(k, i + 1, j - 1) {
                ll K = f[i][k].first + f[k][j].first;
                ll M = f[i][k].second + f[k][j].second + S(i, k, j);
                if (M >= mid) f[i][j] = max(f[i][j], pii(K + 1, 0));
                else f[i][j] = max(f[i][j], pii(K, M));
            }
        }
    }
    return f[1][n].first > k;
}

int main() {
    read(n), read(k);
    FOR(i, 1, n) read(x[i]), read(y[i]);
    ll l = 0, r = 4e18, ans;
    while (l <= r) {
        ll mid = (l + r) >> 1;
        if (check(mid)) ans = mid, l = mid + 1;
        else r = mid - 1;
    }
    print(ans, '\n');
    return output(), 0;
}