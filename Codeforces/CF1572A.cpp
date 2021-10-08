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

const int maxn = 2e5 + 5;
std::vector<int> G[maxn];
int n, q[maxn], head, tail, ind[maxn], f[maxn];

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) G[i].clear(), ind[i] = 0, f[i] = 0;
        FOR(v, 1, n) {
            read(ind[v]);
            FOR(i, 1, ind[v]) {
                int u; read(u);
                G[u].push_back(v);
            }
        }
        head = 1, tail = 0;
        int tot = 0;
        FOR(u, 1, n) if (!ind[u]) q[++tail] = u, f[u] = 1, ++tot;
        while (head <= tail) {
            int u = q[head++];
            for (auto v : G[u]) {
                f[v] = max(f[v], u < v ? f[u] : f[u] + 1);
                if (!--ind[v]) ++tot, q[++tail] = v;
            }
        }
        if (tot < n) print(-1, '\n');
        else {
            int ans = 0;
            FOR(i, 1, n) ans = max(ans, f[i]);
            print(ans, '\n');
        }
    }
    return output(), 0;
}