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
ll x[maxn], a, b, c, f[maxn];
int q[maxn], head, tail;

il ll Y(int i) {return f[i] + a * x[i] * x[i] - b * x[i];}
il ll X(int i) {return x[i];}

int main() {
    n = read();
    a = read(), b = read(), c = read();
    FOR(i, 1, n) x[i] = read() + x[i - 1];
    q[head = tail = 1] = 0;
    FOR(i, 1, n) {
        while (head < tail && Y(q[head + 1]) - Y(q[head]) >= 2ll * a * x[i] * (X(q[head + 1]) - X(q[head]))) ++head;
        int &j = q[head];
        f[i] = f[j] + a * (x[i] - x[j]) * (x[i] - x[j]) + b * (x[i] - x[j]) + c;
        while (head < tail && (Y(q[tail]) - Y(q[tail - 1])) * (X(i) - X(q[tail])) <= (Y(i) - Y(q[tail])) * (X(q[tail]) - X(q[tail - 1]))) --tail;
        q[++tail] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}