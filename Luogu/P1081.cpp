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
void read(char *s) {
    int p = 0;
    char c = getchar();
    while (!isdigit(c) && !isalpha(c)) c = getchar();
    while (isalpha(c) || isdigit(c)) s[p++] = c, c = getchar();
    return;
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
} // namespace fastIO

using namespace fastIO;

using namespace std;
typedef pair<int, int> pii;
const int maxn = 1e5 + 5;
int n;
int h[maxn], f[maxn][20][2][2], g[maxn][20][2];
set<pii> S;

il int myabs(int a) {return a >= 0 ? a : -a;}

int la, lb;

void calc(int s, int x) {
    int p = s;
    la = lb = 0;
    DEC(j, 19, 0) {
        if (~g[p][j][0] && la + lb + f[p][j][0][0] + f[p][j][0][1] <= x) {
            la += f[p][j][0][0];
            lb += f[p][j][0][1];
            p = g[p][j][0];
        }
    }
    return;
}

int main() {
    read(n);
    FOR(i, 1, n) read(h[i]);
    memset(f, 0x3f, sizeof f);
    memset(g, -1, sizeof g);
    S.insert(make_pair(h[n], n));
    DEC(i, n - 1, 1) {
        auto it0 = S.lower_bound(make_pair(h[i], i)), it = it0;
        if (it != S.begin()) {
            --it;
            for (int j = 1; j <= 2; ++j, --it) {
                if (g[i][0][1] == -1 || myabs(h[i] - it->first) < myabs(h[i] - h[g[i][0][1]]))
                    g[i][0][0] = g[i][0][1], g[i][0][1] = it->second;
                else if (g[i][0][0] == -1 || myabs(h[i] - it->first) < myabs(h[i] - h[g[i][0][0]]))
                    g[i][0][0] = it->second;
                if (it == S.begin()) break;
            }
        }
        it = it0;
        for (int j = 1; j <= 2 && it != S.end(); ++j, ++it) {
            if (g[i][0][1] == -1 || myabs(h[i] - it->first) < myabs(h[i] - h[g[i][0][1]]))
                g[i][0][0] = g[i][0][1], g[i][0][1] = it->second;
            else if (g[i][0][0] == -1 || myabs(h[i] - it->first) < myabs(h[i] - h[g[i][0][0]]))
                g[i][0][0] = it->second;
        }
        S.insert(make_pair(h[i], i));
    }
    FOR(i, 1, n) {
        FOR(k, 0, 1) {
            if (~g[i][0][k]) {
                f[i][0][k][k ^ 1] = 0;
                f[i][0][k][k] = myabs(h[g[i][0][k]] - h[i]);
            }
        }
    }
    FOR(j, 1, 19) {
        FOR(i, 1, n) {
            FOR(k, 0, 1) {
                if (j == 1) {
                    if (~g[i][j - 1][k] && ~g[g[i][j - 1][k]][j - 1][k ^ 1]) {
                        g[i][j][k] = g[g[i][j - 1][k]][j - 1][k ^ 1];
                        f[i][j][k][0] = f[i][j - 1][k][0] + f[g[i][j - 1][k]][j - 1][k ^ 1][0];
                        f[i][j][k][1] = f[i][j - 1][k][1] + f[g[i][j - 1][k]][j - 1][k ^ 1][1];
                    }
                } else {
                    if (~g[i][j - 1][k] && ~g[g[i][j - 1][k]][j - 1][k]) {
                        g[i][j][k] = g[g[i][j - 1][k]][j - 1][k];
                        f[i][j][k][0] = f[i][j - 1][k][0] + f[g[i][j - 1][k]][j - 1][k][0];
                        f[i][j][k][1] = f[i][j - 1][k][1] + f[g[i][j - 1][k]][j - 1][k][1];
                    }
                }
            }
        }
    }
    int x0; read(x0);
    int ans = -1;
    double rate = 1e18;
    FOR(s, 1, n) {
        calc(s, x0);
        double now = (!lb ? 1e9 : (double)la / lb);
        if (now < rate) rate = now, ans = s;
        else if (now == rate && h[s] > h[ans])
            rate = now, ans = s;
    }
    print(ans), putchar('\n');
    int m; read(m);
    FOR(i, 1, m) {
        int s, x; read(s), read(x);
        calc(s, x);
        print(la), putchar(' '), print(lb), putchar('\n');
    }
    return output(), 0;
}