#include <cstdio>
#include <cctype>
#include <algorithm>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

namespace fastIO {
    const int maxc = 1 << 21;
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
}

using namespace fastIO;

typedef long long ll;
const int maxn = 2e5 + 5;

typedef struct Point {
    ll x, y;
    Point() {}
    Point(int a, int b) : x(a), y(b) {}
} Vector;

il Vector operator+(const Vector &a, const Vector &b) {return Vector(a.x + b.x, a.y + b.y);}
il Vector operator-(const Vector &a, const Vector &b) {return Vector(a.x - b.x, a.y - b.y);}
il ll operator^(const Vector &a, const Vector &b) {return a.x * b.y - a.y * b.x;}

il bool cmp1(const Point &a, const Point &b) {return a.x == b.x ? a.y < b.y : a.x < b.x;}

void convexHull(int &n, Point *p) {
    static Point stk[maxn];
    static int top;
    std::sort(p + 1, p + n + 1, cmp1);
    top = 0;
    FOR(i, 1, n) {
        while (top >= 2 && ((stk[top] - stk[top - 1]) ^ (p[i] - stk[top - 1])) < 0) --top;
        stk[++top] = p[i];
    }
    DEC(i, n - 1, 1) {
        while (top >= 2 && ((stk[top] - stk[top - 1]) ^ (p[i] - stk[top - 1])) < 0) --top;
        stk[++top] = p[i];
    }
    FOR(i, 1, top) p[i] = stk[i];
    n = top;
    return;
}

int n, m;
Point a[maxn], b[maxn], c[maxn];

void minkowski() {
    int tot;
    c[tot = 1] = a[1] + b[1];
    int i = 1, j = 1;
    while (i < n && j < m) {
        Vector n1 = (a[i] + b[j + 1]) - c[tot], n2 = (a[i + 1] + b[j]) - c[tot];
        if ((n1 ^ n2) < 0)
            c[++tot] = a[i + 1] + b[j], ++i;
        else c[++tot] = a[i] + b[j + 1], ++j;
    }
    for (; i <= n; ++i) c[++tot] = a[i] + b[m];
    for (; j <= m; ++j) c[++tot] = a[n] + b[j];

    ll ans = 0;
    for (int i = 1; i < tot; ++i)
        ans += ((c[i] - c[1]) ^ (c[i + 1] - c[1]));
    printf("%lld\n", ans);
    return;
}

int main() {
    read(n), read(m);
    FOR(i, 1, n) read(a[i].x), read(a[i].y);
    FOR(i, 1, m) read(b[i].x), read(b[i].y);

    convexHull(n, a), convexHull(m, b);
    minkowski();

    return 0;
}