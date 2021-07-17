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

typedef long long ll;

il ll min(ll a, ll b) {return a < b ? a : b;}

const int maxn = 1005;

int h, w;
ll c, a[maxn][maxn], v[maxn][maxn], ans = 1e18;

void solve() {
    FOR(i, 1, h)
        FOR(j, 1, w) v[i][j] = a[i][j] + c * i + c * j;
    DEC(j, w - 1, 1)
        DEC(i, h, 1) v[i][j] = min(v[i][j], v[i][j + 1]);
    DEC(i, h - 1, 1)
        DEC(j, w, 1) v[i][j] = min(v[i][j], v[i + 1][j]);
    FOR(i, 1, h)
        FOR(j, 1, w - 1) ans = min(ans, a[i][j] - c * i - c * j + v[i][j + 1]);
    FOR(i, 1, h - 1)
        FOR(j, 1, w) ans = min(ans, a[i][j] - c * i - c * j + v[i + 1][j]);
}

int main() {
    h = read(), w = read(), c = read();
    FOR(i, 1, h)
        FOR(j, 1, w)
            a[i][j] = read();
    solve();
    FOR(i, 1, h) std::reverse(a[i] + 1, a[i] + w + 1);
    solve();
    printf("%lld\n", ans);
    return 0;
}