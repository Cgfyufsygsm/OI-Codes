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

const int maxn = 1e5 + 5;
vector<int> G[maxn];
int n, a[maxn], b[maxn], a0[maxn], b0[maxn], ia[maxn], ib[maxn];
int dfn[maxn], low[maxn], dfnClock, scc[maxn], ins[maxn], sccCnt, stk[maxn], top;
int ind[maxn];
int ans[maxn];

void tarjan(int u) {
    dfn[u] = low[u] = ++dfnClock;
    stk[++top] = u, ins[u] = 1;
    for (auto v : G[u]) {
        if (!dfn[v])
            tarjan(v), low[u] = min(low[u], low[v]);
        else if (ins[v])
            low[u] = min(low[u], dfn[v]);
    }
    if (low[u] == dfn[u]) {
        ++sccCnt;
        while (true) {
            int now = stk[top--];
            ins[now] = 0;
            scc[now] = sccCnt;
            if (now == u) break;
        }
    }
    return;
}

int main() {
    int T; read(T);
    while (T--) {
        read(n);
        FOR(i, 1, n) read(a[i]), a0[i] = a[i];
        FOR(i, 1, n) read(b[i]), b0[i] = b[i];
        sort(a0 + 1, a0 + n + 1), sort(b0 + 1, b0 + n + 1);
        FOR(i, 1, n) {
            a[i] = lower_bound(a0 + 1, a0 + n + 1, a[i]) - a0;
            b[i] = lower_bound(b0 + 1, b0 + n + 1, b[i]) - b0;
            ia[a[i]] = i, ib[b[i]] = i;
            G[i].clear();
            dfn[i] = low[i] = scc[i] = ins[i] = ind[i] = ans[i] = 0;
        }
        FOR(i, 1, n) {
            if (a[i] != 1)
                G[i].push_back(ia[a[i] - 1]);
            if (b[i] != 1)
                G[i].push_back(ib[b[i] - 1]);
        }
        sccCnt = dfnClock = 0;
        FOR(i, 1, n) if (!dfn[i]) tarjan(i);
        FOR(i, 1, n) {
            if (a[i] != 1 && scc[i] != scc[ia[a[i] - 1]])
                ++ind[scc[ia[a[i] - 1]]];
            if (b[i] != 1 && scc[i] != scc[ib[b[i] - 1]])
                ++ind[scc[ib[b[i] - 1]]];
        }
        int ansid = 0;
        FOR(i, 1, sccCnt) if (!ind[i]) ansid = i;
        FOR(i, 1, n) putchar(scc[i] == ansid ? '1' : '0');
        putchar('\n');
    }
    return output(), 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}