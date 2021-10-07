#include <cstdio>
#include <cctype>
#include <vector>
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
template<typename T> void print(const T &x) {
    if (x < 0) putchar('-'), print(-x);
    else {
        if (x > 9) print(x / 10);
        putchar(x % 10 + '0');
    }
    return;
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

const int maxn = 1e5 + 5;
std::vector<int> G[maxn];
int n, k, a[maxn], sum[maxn], cnt0[maxn], cntk[maxn];
int xorsum = 0;

bool dfs(int u, int fa) {
    sum[u] = a[u];
    int tmpk = 0, tmp0 = 0;
    for (auto v : G[u]) {
        if (v == fa) continue;
        if (dfs(v, u)) return true;
        sum[u] ^= sum[v];
        if (cntk[v]) ++tmpk;
        if (cnt0[v]) ++tmp0;
        if (tmpk >= 2) return true;
    }
    if (!sum[u] && tmpk) return true;
    cnt0[u] = ((tmp0 ? 1 : 0) | (sum[u] == 0));
    cntk[u] = ((tmpk ? 1 : 0) | (sum[u] == xorsum));
    return false;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n), read(k);
        xorsum = 0;
        FOR(i, 1, n) G[i].clear(), read(a[i]), xorsum ^= a[i];
        FOR(i, 1, n - 1) {
            int u, v; read(u), read(v);
            G[u].push_back(v), G[v].push_back(u);
        }
        if (!xorsum) puts("YES");
        else {
            if (k >= 3 && dfs(1, 0)) puts("YES");
            else puts("NO");
        }
    }
    return output(), 0;
}