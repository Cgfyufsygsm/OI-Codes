#include <cstdio>
#include <cctype>
#include <cstring>
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

const int maxn = 3005;
typedef long long ll;

int n, m;
ll x[maxn], f[maxn], g[maxn];
int q[maxn], head, tail;

il ll X(int i) {return x[i];}
il ll Y(int i) {return g[i] + 2 * x[n] * x[i] + m * x[i] * x[i];}

int main() {
    n = read(), m = read();
    FOR(i, 1, n) x[i] = read() + x[i - 1];
    FOR(i, 1, n) f[i] = m * x[i] * x[i] - 2 * x[i] * x[n];
    FOR(k, 2, m) {
        memcpy(g, f, sizeof f);
        q[head = tail = 1] = 0;
        FOR(i, 1, n) {
            ll k = 2 * m * x[i];
            while (head < tail && Y(q[head + 1]) - Y(q[head]) <= k * (X(q[head + 1]) - X(q[head]))) ++head;
            int &j = q[head];
            f[i] = g[j] + m * (x[i] - x[j]) * (x[i] - x[j]) - 2 * (x[i] - x[j]) * x[n];
            while (head < tail && (Y(q[tail]) - Y(q[tail - 1])) * (X(i) - X(q[tail])) >= (Y(i) - Y(q[tail])) * (X(q[tail]) - X(q[tail - 1]))) --tail;
            q[++tail] = i;
        }
    }
    printf("%lld\n", f[n] + x[n] * x[n]);
    return 0;
}