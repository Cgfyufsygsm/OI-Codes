#include <cstdio>
#include <cctype>
#include <vector>
#include <set>
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

typedef long long ll;
const int maxn = 1e5 + 5;
std::vector<int> G[maxn];
int n, s, a[maxn];
ll ans;
std::set<ll> S;

void dfs(int u, int fa, ll now) {
    now += a[u];
    S.insert(now);
    if (S.count(now - s)) ++ans;
    for (auto v : G[u]) if (v != fa) dfs(v, u, now);
    S.erase(now);
    return;
}

int main() {
    read(n), read(s);
    FOR(i, 1, n) read(a[i]);
    FOR(i, 1, n - 1) {
        int u, v; read(u), read(v);
        G[u].push_back(v), G[v].push_back(u);
    }
    S.insert(0);
    dfs(1, 0, 0);
    print(ans);
    return output(), 0;
}