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
template<typename T> il T chkmax(T &a, const T &b) {return a = (b > a ? b : a);}
template<typename T> il T chkmin(T &a, const T &b) {return a = (b < a ? b : a);}
template<typename T> il T myabs(const T &a) {return a >= 0 ? a : -a;}
template<typename T> il void myswap(T &a, T &b) {
    T t = a;
    a = b, b = t;
    return;
}

const int maxn = 1e4 + 5, W = 1e7 + 5;
int head[maxn], cnte, vis[maxn], n, m, buc[W];
int root, tot, maxp[maxn], size[maxn], dis[maxn], query[maxn], ans[maxn], maxq;

struct Edge {
    int to, nxt, w;
} e[maxn << 1];

il void add(int u, int v, int w) {
    e[++cnte].to = v;
    e[cnte].w = w;
    e[cnte].nxt = head[u];
    head[u] = cnte;
    return;
}

void getRt(int u, int fa) {
    size[u] = 1, maxp[u] = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == fa || vis[v]) continue;
        getRt(v, u);
        size[u] += size[v];
        chkmax(maxp[u], size[v]);
    }
    chkmax(maxp[u], tot - size[u]);
    if (maxp[u] < maxp[root]) root = u;
    return;
}

void getDis(int u, int fa, int *now) {
    if (dis[u] > maxq) return;
    now[++now[0]] = dis[u];
    for (int i = head[u]; i; i = e[i].nxt) {
        int &v = e[i].to;
        if (v == fa || vis[v]) continue;
        dis[v] = dis[u] + e[i].w;
        getDis(v, u, now);
    }
    return;
}

void calc(int u) {
    static int q[maxn], now[maxn], cnt; // q 维护加入了桶的元素, now 维护当前子树内的元素
    cnt = 0;
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (vis[v]) continue;
        now[0] = 0, dis[v] = e[i].w;
        getDis(v, u, now);
        FOR(j, 1, now[0]) // 开始合并答案
            FOR(k, 1, m)
                if (query[k] >= now[j])
                    ans[k] |= buc[query[k] - now[j]];
        FOR(j, 1, now[0])
            buc[now[j]] = 1, q[++cnt] = now[j]; // 加入桶
    }
    FOR(i, 1, cnt) buc[q[i]] = 0; // 清空桶
    return;
}

void divide(int u) {
    vis[u] = buc[0] = 1; // 删掉 u 点并初始化桶
    calc(u); // 计算当前点的答案
    for (int i = head[u]; i; i = e[i].nxt) {
        int v = e[i].to;
        if (vis[v]) continue;
        maxp[0] = n, tot = size[v], root = 0;
        getRt(v, u); // 找到子树重心
        getRt(root, 0); // 获取子树中正确的 size
        divide(root);
    }
    return;
}

int main() {
    read(n, m);
    FOR(i, 2, n) {
        int u, v, w; read(u, v, w);
        add(u, v, w), add(v, u, w);
    }
    FOR(i, 1, m) read(query[i]);
    maxq = *max_element(query + 1, query + m + 1);

    maxp[0] = n;
    getRt(1, 0);
    getRt(root, 0);
    divide(root);

    FOR(i, 1, m) print(ans[i] ? "AYE" : "NAY");
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}