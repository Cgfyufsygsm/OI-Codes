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
const int maxn = 2e5 + 5, N = 2e5;
ll a[maxn], b[maxn], n, mu[maxn], d[maxn], add;

vector<ll> f;

int main() {
    mu[1] = 1;
    FOR(i, 2, N) {
        --mu[i];
        for (int j = 2 * i; j <= N; j += i)
            mu[j] -= mu[i];
    }
    read(n);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n) read(b[i]), b[i] -= a[i];
    b[1] = 0;
    FOR(i, 1, n) {
        d[i] = b[i];
        for (int j = 2 * i; j <= n; j += i) b[j] -= d[i];
    }
    FOR(i, 1, n) {
        if (!mu[i]) add += myabs(d[i]);
        else if (mu[i] == 1) f.emplace_back(d[i]);
        else f.emplace_back(-d[i]);
    }
    sort(f.begin(), f.end());
    auto sum = f;
    for (int i = 1; i < sum.size(); ++i) sum[i] += sum[i - 1];
    auto getsum = [&sum](int l, int r) {
        if (r < 0) return 0ll;
        ll res = sum[r];
        if (l - 1 >= 0) res -= sum[l - 1];
        return res;
    };
    int q; read(q);
    while (q--) {
        ll x; read(x);
        x -= a[1];
        int l = 0, r = sum.size() - 1;
        while (l <= r) {
            int mid = (l + r) >> 1;
            if (f[mid] <= -x) l = mid + 1;
            else r = mid - 1;
        }
        ll ans = getsum(l, sum.size() - 1) + (sum.size() - l) * x;
        ans -= getsum(0, r) + (r + 1) * x;
        print(ans + add, '\n');
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}