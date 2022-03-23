#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {

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

const int maxn = 3e4 + 5;
int head[maxn], to[maxn << 1], nxt[maxn << 1], cnte, n, m;
char ch[maxn << 1], s[maxn << 1], las[maxn << 1];
int beg[maxn], len[maxn], fa[maxn], nfd[maxn], dfnCnt;
bitset<maxn << 1> f[maxn], g[maxn], tr[26], init, ans, t1, t2;

il void add(int u, int v, char c) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    ch[cnte] = c;
    head[u] = cnte;
    return;
}

void dfs(int u, int pre) {
    nfd[++dfnCnt] = u;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa[u]) continue;
        fa[v] = u, las[v] = ch[i];
        dfs(v, u);
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin >> n;
    FOR(i, 1, n - 1) {
        int u, v; char c; 
        cin >> u >> v >> c;
        add(u, v, c), add(v, u, c);
    }
    cin >> m;
    FOR(i, 1, m) {
        beg[i] = beg[i - 1] + len[i - 1] + 1;
        cin >> s + beg[i];
        len[i] = strlen(s + beg[i]);
    }
    FOR(i, 0, beg[m] + len[m]) {
        if (!s[i]) init[i] = 1;
        else tr[s[i] - 'a'][i] = 1;
    }
    dfs(1, 0);
    FOR(i, 1, n) f[i] = g[i] = init;
    DEC(id, n, 2) {
        int v = nfd[id], u = fa[v];
        t1 = (f[v] << 1) & tr[las[v] - 'a'];
        t2 = (g[v] >> 1) & tr[las[v] - 'a'];
        ans |= (f[u] & (t2 >> 1));
        ans |= ((g[u] >> 1) & t1);
        f[u] |= t1, g[u] |= t2;
    }
    FOR(i, 1, m) {
        bool flg = 0;
        FOR(j, beg[i] - 1, beg[i] + len[i] - 1) flg |= ans[j];
        cout << (flg ? "YES\n" : "NO\n");
    }
    return 0;
}

} // namespace YangTY

int main() {
    YangTY::main();
    return 0;
}