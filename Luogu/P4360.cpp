#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)
#define int long long

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

const int maxn = 50005;
int n;
int w[maxn], d[maxn], v[maxn];
int f[maxn][4];//f[i][k] 第 i 棵树的地方，强制建锯木厂，建了 k 个
int q[maxn][4], head[4], tail[4];

il int X(int i) {return w[i];}
il int Y(int i, int k) {return f[i][k] + v[i];}

signed main() {
    n = read();
    FOR(i, 1, n) w[i] = read(), d[i + 1] = read() + d[i];
    ++n;
    FOR(i, 1, n) v[i] = w[i] * d[i] + v[i - 1], w[i] += w[i - 1];
    head[0] = tail[0] = 1;
    FOR(k, 1, 3) {
        FOR(i, 1, n) {
            while (head[k - 1] < tail[k - 1] && Y(q[head[k - 1] + 1][k - 1], k - 1) - Y(q[head[k - 1]][k - 1], k - 1) <= d[i] * (X(q[head[k - 1] + 1][k - 1]) - X(q[head[k - 1]][k - 1]))) ++head[k - 1];
            int &j = q[head[k - 1]][k - 1];
            f[i][k] = f[j][k - 1] + v[j] + d[i] * (w[i] - w[j]) - v[i];
            while (head[k] < tail[k] && (Y(q[tail[k]][k], k) - Y(q[tail[k] - 1][k], k)) * (X(i) - X(q[tail[k]][k])) >= (Y(i, k) - Y(q[tail[k]][k], k)) * (X(q[tail[k]][k]) - X(q[tail[k] - 1][k]))) --tail[k];
            q[++tail[k]][k] = i;
        }
    }
    printf("%lld\n", f[n][3]);
    return 0;
}