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
    while (isspace(c)) c = getchar();
    while (~c && !isspace(c)) s[p++] = c, c = getchar();
    return;
}
template<typename T1, typename... T2> void read(T1 &a, T2&... x) {
    read(a), read(x...);
    return;
}
char obuf[maxc], *__pO = obuf;
il void putchar(char c) {*__pO++ = c;}
template<typename T> void print(T x, char c = '\n') {
    static char stk[50];
    int top = 0;
    if (x < 0) putchar('-'), x = -x;
    if (x) {
        for (; x; x /= 10) stk[++top] = x % 10 + '0';
        while (top) putchar(stk[top--]);
    } else putchar('0');
    putchar(c);
    return;
}
void print(char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
void print(const char *s, char c = '\n') {
    for (int i = 0; s[i]; ++i) putchar(s[i]);
    putchar(c);
    return;
}
template<typename T1, typename... T2> il void print(T1 a, T2... x) {
    if (!sizeof...(x)) print(a);
    else print(a, ' '), print(x...);
    return;
}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
} // namespace fastIO

using namespace fastIO;

template<typename T> il T max(const T &a, const T &b) {return a > b ? a : b;}
template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}
template<typename T, typename...Args> il T max(const T &a, const Args&... args) {
    T res = max(args...);
    return max(a, res);
}
template<typename T, typename...Args> il T min(const T &a, const Args&... args) {
    T res = min(args...);
    return min(a, res);
}
template<typename T> il T chkmax(T &a, const T &b) {return a = max(a, b);}
template<typename T> il T chkmin(T &a, const T &b) {return a = min(a, b);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1005;
struct edge {
    int to, id;
    edge(int v, int i) : to(v), id(i) {}
};
vector<edge> G[maxn];
vector<int> ans;
int n, m, p[maxn], ind[maxn], fa[maxn];

int find(int u) {return fa[u] == u ? u : fa[u] = find(fa[u]);}

bool merge(int x, int y) {
    x = find(x), y = find(y);
    if (x == y) return 0;
    else return fa[y] = x, 1;
}

bool dfs(int u, int fa, int t) {
    if (u == t) return 1;
    for (auto &e : G[u]) {
        int v = e.to;
        if (v == fa) continue;
        if (dfs(v, u, t)) {
            ans.push_back(e.id);
            swap(p[u], p[v]);
            return 1;
        }
    }
    return 0;
}

int main() {
    read(n);
    FOR(i, 1, n) read(p[i]), fa[i] = i;
    read(m);
    FOR(i, 1, m) {
        int a, b; read(a, b);
        if (merge(a, b)) {
            ++ind[a], ++ind[b];
            G[a].push_back(edge(b, i));
            G[b].push_back(edge(a, i));
        }
    }
    FOR(cnt, 1, n) {
        FOR(i, 1, n) if (ind[i] == 1) {
            int t = -1;
            FOR(j, 1, n) if (p[j] == i) t = j;
            if (t == -1 || !dfs(i, 0, t)) return puts("-1"), 0;
            --ind[i];
            for (auto e : G[i]) --ind[e.to];
            break;
        }
    }
    print(ans.size());
    for (auto i : ans) print(i, ' ');
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}