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
const int maxn = 1e5 + 5, maxh = 1e6;

il ll min(ll a, ll b) {return a < b ? a : b;}

int n;
ll w[maxn], h[maxn], f[maxn];
ll K[maxn], B[maxn];

int t[4 * maxh + 5];

il ll calc(ll X, int i) {return i ? K[i] * X + B[i] : 1e18;}

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void insert(int i, int j, int k, int u) {
    int v = t[k];
    ll resu = calc(M, u), resv = calc(M, v);
    if (i >= j) {
        if (resu < resv) t[k] = u;
        return;
    }
    if (K[u] > K[v]) {
        if (resu < resv)
            t[k] = u, insert(M + 1, j, R, v);
        else insert(i, M, L, u);
    }
    else if (K[u] < K[v]) {
        if (resu < resv)
            t[k] = u, insert(i, M, L, v);
        else insert(M + 1, j, R, u);
    }
    else if (resu < resv) t[k] = u;
    return;
}

ll query(int i, int j, int k, ll X) {
    ll ret = calc(X, t[k]);
    if (i == j) return ret;
    if (X <= M) return min(query(i, M, L, X), ret);
    else return min(query(M + 1, j, R, X), ret);
}

int main() {
    n = read();
    FOR(i, 1, n) h[i] = read();
    FOR(i, 1, n) w[i] = w[i - 1] + read();
    f[1] = 0;
    K[1] = -2 * h[1], B[1] = f[1] + h[1] * h[1] - w[1];
    insert(1, maxh, 1, 1);
    FOR(i, 2, n) {
        f[i] = query(1, maxh, 1, h[i]) + h[i] * h[i] + w[i - 1];
        K[i] = -2 * h[i], B[i] = f[i] + h[i] * h[i] - w[i];
        insert(1, maxh, 1, i);
    }
    printf("%lld\n", f[n]);
    return 0;
}