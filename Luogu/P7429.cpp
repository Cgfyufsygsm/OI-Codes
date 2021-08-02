#include <cstdio>
#include <cctype>
#include <cmath>
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
    char obuf[maxc], *__pO = obuf;
    il void putchar(char c) {*__pO++ = c;}
    template<typename T> void print(T x) {
        if (x < 0) putchar('-'), print(-x);
        else {
            if (x > 9) print(x / 10);
            putchar(x % 10 + '0');
        }
        return;
    }
    void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

using namespace fastIO;

const int maxn = 40, mod = 1e9 + 7, inv2 = 5e8 + 4;

struct Point {
    int dim;
    int x[maxn];
} p[maxn];

Point operator-(const Point &a, const Point &b) {
    Point ret;
    ret.dim = a.dim;
    FOR(i, 1, ret.dim) ret.x[i] = a.x[i] - b.x[i];
    return ret;
}

typedef double db;
db mat[maxn][maxn];
int n;

double det(int n, db a[40][40]) {
    FOR(i, 1, n) {
        int r = i;
        FOR(j, i + 1, n)
            if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        std::swap(a[r], a[i]);
        FOR(k, 1, n) {
            if (k == i) continue;
            db div = a[k][i] / a[i][i];
            FOR(j, i + 1, n) a[k][j] -= div * a[i][j];
        }
    }
    db ret = 1;
    FOR(i, 1, n) ret *= a[i][i];
    return ret;
}

int main() {
    int t;
    read(t);
    while (t--) {
        read(n);
        FOR(i, 1, n + 1) {
            p[i].dim = n - 1;
            FOR(j, 1, n - 1) read(p[i].x[j]);
        }
        int ans = 0;
        FOR(ban, 1, n + 1) {
            int st = (ban == 1) ? 2 : 1;
            for (int j = 1, col = 1; j <= n + 1 && col <= n - 1; ++j, ++col) {
                while (j == st || j == ban) ++j;
                Point tmp = p[j] - p[st];
                FOR(r, 1, n - 1) mat[r][col] = tmp.x[r];
            }
            ans = (ans + (long long)fabs(round(det(n - 1, mat)))) % mod;
        }
        print(1ll * ans * inv2 % mod), putchar('\n');
    }
    return output(), 0;
}