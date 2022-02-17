#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

namespace YangTY {

const int mod = 998244353;

struct modint {
    typedef int INT;
    static const INT mod = YangTY::mod;
    INT val;
    il void check() {
        val >= mod ? val %= mod : true;
        val < 0 ? (val %= mod) += mod : true;
        return;
    }
    modint(INT v = 0) : val(v) {check();}

    il modint &operator=(INT v) {return val = v, *this;}
    il modint &operator+=(modint rhs) {return val = val + rhs.val >= mod ? val + rhs.val - mod : val + rhs.val, *this;}
    il modint &operator-=(modint rhs) {return val = val - rhs.val < 0 ? val - rhs.val + mod : val - rhs.val, *this;}
    il modint &operator*=(modint rhs) {return val = 1ll * val * rhs.val % mod, *this;}

    il friend modint operator+(const modint &lhs, const modint &rhs) {return modint(lhs) += rhs;}
    il friend modint operator-(const modint &lhs, const modint &rhs) {return modint(lhs) -= rhs;}
    il friend modint operator*(const modint &lhs, const modint &rhs) {return modint(lhs) *= rhs;}
    il friend bool operator==(const modint &lhs, const modint &rhs) {return lhs.val == rhs.val;}
    il friend bool operator!=(const modint &lhs, const modint &rhs) {return lhs.val != rhs.val;}
    il friend bool operator>(const modint &lhs, const modint &rhs) {return lhs.val > rhs.val;}
    il friend bool operator<(const modint &lhs, const modint &rhs) {return lhs.val < rhs.val;}
    il friend bool operator>=(const modint &lhs, const modint &rhs) {return lhs.val >= rhs.val;}
    il friend bool operator<=(const modint &lhs, const modint &rhs) {return lhs.val <= rhs.val;}

    il modint &operator++() {
        ++val;
        if (val == mod) val = 0;
        return *this;
    }
    il modint &operator--() {
        if (val == 0) val = mod;
        --val;
        return *this;
    }
    il modint operator++(int) {
        modint ret = *this;
        ++*this;
        return ret;
    }
    il modint operator--(int) {
        modint ret = *this;
        --*this;
        return ret;
    }

    il modint operator+() const {return *this;}
    il modint operator-() const {return modint() - *this;}
};

modint qPow(modint base, modint exp) {
    base.check();
    modint ret = 1;
    for (auto p = exp.val; p; p >>= 1, base *= base)
        if (p & 1) ret *= base;
    return ret;
}

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
il void print(modint x, char c = '\n') {print(x.val, c);}
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

const int maxn = 5e5 + 5;
int n, m, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte, anc[maxn], dep[maxn];

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs0(int u, int fa) {
    dep[u] = dep[fa] + 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa) continue;
        dfs0(v, u);
    }
    return;
}

struct node {
    modint sum, mul;
    int ch[2];
    node() : mul(1) {}
} t[maxn * 50];
int root[maxn], tot;

#define ls(u) t[u].ch[0]
#define rs(u) t[u].ch[1]
#define M ((i + j) >> 1)

int insert(int u, int i, int j, int x) {
    if (!u) u = ++tot;
    ++t[u].sum;
    if (i == j) return u;
    if (x <= M) ls(u) = insert(ls(u), i, M, x);
    else rs(u) = insert(rs(u), M + 1, j, x);
    return u;
}

il void pushup(int u) {
    t[u].sum = t[ls(u)].sum + t[rs(u)].sum;
    return;
}

il void pushtag(int u, modint x) {
    t[u].sum *= x, t[u].mul *= x;
    return;
}

il void pushdown(int u) {
    if (t[u].mul == 1) return;
    pushtag(ls(u), t[u].mul), pushtag(rs(u), t[u].mul);
    t[u].mul = 1;
}

int merge(int x, int y, int i, int j, modint &sumx, modint &sumy) {
    if (!x && !y) return 0;
    if (!x && y) {
        sumy += t[y].sum;
        pushtag(y, sumx);
        return y;
    }
    if (x && !y) {
        sumx += t[x].sum;
        pushtag(x, sumy);
        return x;
    }
    if (i == j) {
        sumx += t[x].sum;
        t[x].sum = t[x].sum * sumy + t[y].sum * sumx;
        sumy += t[y].sum;
        return x;
    }
    pushdown(x), pushdown(y);
    ls(x) = merge(ls(x), ls(y), i, M, sumx, sumy);
    rs(x) = merge(rs(x), rs(y), M + 1, j, sumx, sumy);
    return pushup(x), x;
}

modint query(int u, int i, int j, int x, int y) {
    if (x <= i && y >= j) return t[u].sum;
    pushdown(u);
    modint ret = 0;
    if (x <= M) ret += query(ls(u), i, M, x, y);
    if (y > M) ret += query(rs(u), M + 1, j, x, y);
    return ret;
}

void dfs(int u, int fa) {
    root[u] = insert(root[u], 0, n, dep[anc[u]]);
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        modint sumx = 0, sumy = query(root[v], 0, n, 0, dep[v] - 1);
        root[u] = merge(root[u], root[v], 0, n, sumx, sumy);
    }
    return;
}

int main() {
    read(n);
    FOR(i, 1, n - 1) {
        int u, v; read(u, v);
        add(u, v), add(v, u);
    }
    dfs0(1, 0);
    read(m);
    FOR(i, 1, m) {
        int u, v; read(u, v);
        if (dep[u] > dep[anc[v]]) anc[v] = u;
    }
    dfs(1, 0);
    print(query(root[1], 0, n, 0, 0));
    return output(), 0;
}
}// namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
