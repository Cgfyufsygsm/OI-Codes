#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {
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

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 2e5 + 5;
vector<int> G[maxn], num[18];
int n, ans[maxn], vis[maxn];

void dfs(int u, int fa, int col, vector<int> *vec) {
    vec[col].push_back(u);
    for (auto v : G[u]) if (v != fa)
        dfs(v, u, col ^ 1, vec);
    return;
}

int main() {
    FOR(i, 1, 2e5)
        num[31 - __builtin_clz(i)].push_back(i);
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) G[i].clear(), ans[i] = vis[i] = 0;
        FOR(i, 1, n - 1) {
            int u, v; read(u), read(v);
            G[u].push_back(v), G[v].push_back(u);
        }
        vector<int> vec[2];
        vec[0].clear(), vec[1].clear();
        dfs(1, 0, 0, vec);
        if (vec[0].size() > vec[1].size()) swap(vec[0], vec[1]);
        int w = vec[0].size();
        FOR(i, 0, 17) if ((1 << i) & w) {
            for (auto x : num[i]) {
                ans[vec[0].back()] = x;
                vis[x] = 1;
                vec[0].pop_back();
            }
        }
        FOR(i, 1, n) if (!vis[i]) {
            ans[vec[1].back()] = i;
            vis[i] = 1;
            vec[1].pop_back();
        }
        FOR(i, 1, n) print(ans[i], ' ');
        putchar('\n');
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}