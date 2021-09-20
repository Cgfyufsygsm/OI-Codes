#include <cstdio>
#include <cctype>
#include <cstring>
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

int a[10][10], vis[10][10], tot, col[10][10];

const int fx[] = {0, 0, 1, -1};
const int fy[] = {1, -1, 0, 0};

il bool check(int i, int j) {return 0 <= i && i <= 5 && 0 <= j && j <= 5;}

void dfs(int i, int j) {
    vis[i][j] = 1;
    FOR(k, 0, 3) {
        int tx = i + fx[k], ty = j + fy[k];
        if (!check(tx, ty) || vis[tx][ty]) continue;
        if (col[i][j] != col[tx][ty]) continue;
        dfs(tx, ty);
    }
    return;
}

int main() {
    FOR(i, 1, 4) FOR(j, 1, 4) read(a[i][j]);
    int ans = 0;
    FOR(S, 0, (1 << 16) - 1) {
        FOR(i, 1, 4) {
            FOR(j, 1, 4) {
                if ((1 << ((i - 1) * 4 + j - 1)) & S)
                    col[i][j] = 1;
                else col[i][j] = 0;
            }
        }
        int ok = 1;
        FOR(i, 1, 4) FOR(j, 1, 4) if (a[i][j] && !col[i][j]) ok = 0;
        tot = 1;
        memset(vis, 0, sizeof vis);
        dfs(0, 0);
        FOR(i, 1, 4) FOR(j, 1, 4) if (!vis[i][j]) ++tot, dfs(i, j);
        if (tot > 2) ok = 0;
        ans += ok;
    }
    print(ans);
    return output(), 0;
}