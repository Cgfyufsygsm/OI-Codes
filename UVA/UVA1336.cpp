#include <cstdio>
#include <cctype>
#include <cstring>
#include <cmath>
#include <algorithm>
#define FOR(i, a, b) for (int i = a; i <= b; ++i)
#define DEC(i, a, b) for (int i = a; i >= b; --i)

const int maxn = 1005;
typedef double db;

int read()
{
    int s = 0, x = 0;
    char c = getchar();
    while (!isdigit(c))
        x |= (c == '-'), c = getchar();
    while (isdigit(c))
        s = s * 10 + c - '0', c = getchar();
    return x ? -s : s;
}

inline db min(db a, db b) {return a < b ? a : b;}

int n, V, X;

struct node
{
    int x, d;
    bool operator<(const node &b) const {return x < b.x;}
} p[maxn];

int dsum[maxn];

db f[maxn][maxn][2];

int main()
{
    while (scanf("%d %d %d", &n, &V, &X) != EOF && n && V && X)
    {
        db ans = 0;
        FOR(i, 1, n) p[i].x = read(), ans += read(), p[i].d = read();
        p[n + 1].x = X, p[n + 1].d = 0;
        ++n;
        std::sort(p + 1, p + n + 1);
        FOR(i, 1, n) dsum[i] = dsum[i - 1] + p[i].d;
        memset(f, 127, sizeof f);
        FOR(i, 1, n) if (p[i].x == X) f[i][i][0] = f[i][i][1] = 0;
        FOR(len, 2, n)
            for (int i = 1, j = i + len - 1; j <= n; ++i, ++j)
            {
                f[i][j][0] = min(f[i + 1][j][0] + (double(p[i + 1].x - p[i].x) / double(V)) * (dsum[n] - (dsum[j] - dsum[i])),
                                 f[i + 1][j][1] + (double(p[j].x - p[i].x) / double(V)) * (dsum[n] - (dsum[j] - dsum[i])));
                f[i][j][1] = min(f[i][j - 1][1] + (double(p[j].x - p[j - 1].x) / double(V)) * (dsum[n] - (dsum[j - 1] - dsum[i - 1])),
                                 f[i][j - 1][0] + (double(p[j].x - p[i].x) / double(V)) * (dsum[n] - (dsum[j - 1] - dsum[i - 1])));
            }
        printf("%d\n", (int)floor(ans + min(f[1][n][0], f[1][n][1])));
    }
    return 0;
}