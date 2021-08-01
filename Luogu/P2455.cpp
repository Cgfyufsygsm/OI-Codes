#include <cstdio>
#include <cctype>
#include <algorithm>
#include <cmath>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

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

typedef double db;
const int maxn = 55;
const db EPS = 1e-8;
int n;
db a[maxn][maxn];

int main() {
    read(n);
    FOR(i, 1, n)
        FOR(j, 1, n + 1)
            read(a[i][j]);
    
    int line = 1;
    FOR(i, 1, n) {
        int r = line;
        FOR(j, i + 1, n)
            if (fabs(a[j][i]) > fabs(a[r][i])) r = j;
        if (fabs(a[r][i]) < EPS) continue;
        std::swap(a[line], a[r]);
        FOR(j, 1, n) {
            if (j == line) continue;
            db mul = a[j][i] / a[line][i];
            FOR(k, i + 1, n + 1)
                a[j][k] -= mul * a[line][k];
        }
        ++line;
    }

    if (line <= n) {
        while (line <= n)
            if (fabs(a[line++][n + 1]) > EPS)
                return puts("-1"), 0;
        return puts("0"), 0;
    }

    FOR(i, 1, n) {
        printf("x%d=", i);
        if (fabs(a[i][n + 1] / a[i][i]) < EPS) puts("0.00");
        else printf("%.2lf\n", a[i][n + 1] / a[i][i]);
    }
    return 0;
}