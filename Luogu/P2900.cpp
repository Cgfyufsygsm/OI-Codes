#include <cstdio>
#include <cctype>
#include <algorithm>
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

const int maxn = 5e4 + 5;
typedef long long ll;
const ll maxw = 1e6;

int n;

struct node {
    ll a, b;
} a[maxn], b[maxn];

il bool cmp1(node x, node y) {return x.a == y.a ? x.b > y.b : x.a > y.a;}

ll f[maxn];

il ll X(int i) {return -b[i + 1].a;}
il ll Y(int i) {return f[i];}

int q[maxn], head, tail;

int main() {
    n = read();
    FOR(i, 1, n) a[i].a = read(), a[i].b = read();
    std::sort(a + 1, a + n + 1, cmp1);
    int cnt = 0;
    FOR(i, 1, n) if (b[cnt].b < a[i].b) b[++cnt] = a[i];
    n = cnt;
    // a 单调减， b 单调增
    // f[i] = min(f[i], f[j - 1] + b[j].a * b[i].b)
    q[head = tail = 1] = 0;
    FOR(i, 1, n) {
        while (head < tail && (Y(q[head + 1]) - Y(q[head])) <= b[i].b * (X(q[head + 1]) - X(q[head]))) ++head;
        f[i] = f[q[head]] + b[q[head] + 1].a * b[i].b;
        while (head < tail && (Y(q[tail]) - Y(q[tail - 1])) * (X(i) - X(q[tail])) >= (Y(i) - Y(q[tail])) * (X(q[tail]) - X(q[tail - 1]))) --tail;
        q[++tail] = i;
    }
    printf("%lld\n", f[n]);
    return 0;
}