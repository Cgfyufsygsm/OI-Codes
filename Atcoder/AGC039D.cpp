#include <bits/stdc++.h>
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
}// namespace fastIO

using namespace fastIO;

using db = long double;
const db PI = acos(-1.0);
const int maxn = 3005;

int n, L, t[maxn];

int main() {
    read(n), read(L);
    FOR(i, 1, n) read(t[i]);
    db ansx = 0, ansy = 0;
    FOR(i, 1, n) {
        FOR(j, i + 1, n) {
            ansx += (n - 2 * (j - i)) * cos(PI * (t[i] + t[j]) / L);
            ansy += (n - 2 * (j - i)) * sin(PI * (t[i] + t[j]) / L);
        }
    }
    db cnt = 1.0 * n * (n - 1) * (n - 2) / 6;
    printf("%.12Lf %.12Lf\n", ansx / cnt, ansy / cnt);
    return 0;
}