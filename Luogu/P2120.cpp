#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

namespace fastIO {
    const int maxc = 1e7 + 5;
    char buf[maxc], *p1 = buf, *p2 = buf;
    il char getchar() {return p1 == p2 && (p2 = (p1 = buf) + fread(buf, 1, maxc, stdin), p1 == p2) ? EOF : *p1++;}
    int read() {
        int s = 0, x = 0;
        char c = getchar();
        while (!isdigit(c))
            x |= (c == '-'), c = getchar();
        while (isdigit(c))
            s = s * 10 + c - '0', c = getchar();
        return x ? -s : s;
    }
}

using namespace fastIO;

typedef long long ll;
const int maxn = 1e6 + 5;

int n;
ll x[maxn], v[maxn], psum[maxn], c[maxn], p[maxn];
ll f[maxn];
// f[i] = min(f[j] + c[i] + )
il ll X(int i) {return psum[i];}
il ll Y(int i) {return f[i] + v[i];}
il ll min(ll a, ll b) {return a < b ? a : b;}

int q[maxn], head, tail;

int main() {
    n = read();
    FOR(i, 1, n) x[i] = read(), p[i] = read(), c[i] = read();
    FOR(i, 1, n) v[i] = v[i - 1] + x[i] * p[i], psum[i] = p[i] + psum[i - 1];
    q[head = tail = 1] = 0;
    FOR(i, 1, n) {
        while (head < tail && (Y(q[head + 1]) - Y(q[head])) < x[i] * (X(q[head + 1]) - X(q[head]))) ++head;
        int &j = q[head];
        f[i] = f[j] + x[i] * (psum[i] - psum[j]) + v[j] - v[i] + c[i];
        while (head < tail && (Y(q[tail]) - Y(q[tail - 1])) * (X(i) - X(q[tail])) >= (Y(i) - Y(q[tail])) * (X(q[tail]) - X(q[tail - 1]))) --tail;
        q[++tail] = i;
    }
    ll ans = f[n];
    DEC(i, n, 1) {
        ans = min(f[i], ans);
        if (p[i]) break;
    }
    printf("%lld\n", ans);
    return 0;
}