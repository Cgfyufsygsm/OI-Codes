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

const int maxn = 3e5 + 5;
const modint inv10000 = qPow(10000, mod - 2);

int n, son[maxn][2], root[maxn], tot;
int v0[maxn], v[maxn], vtot;
modint p[maxn], d[maxn];
struct node {
    modint mul, sum;
    int ch[2];
    node() : mul(1) {}
} t[maxn * 50];

#define ls(k) t[k].ch[0]
#define rs(k) t[k].ch[1]
#define M ((i + j) >> 1)

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
    return;
}

int init(int u, int i, int j, int x) {
    if (!u) u = ++tot;
    t[u].sum += 1;
    if (i == j) return u;
    if (x <= M) ls(u) = init(ls(u), i, M, x);
    else rs(u) = init(rs(u), M + 1, j, x);
    return u;
}

int merge(int x, int y, modint lx, modint rx, modint ly, modint ry, modint p) {
    if (!x && !y) return 0;
    pushdown(x), pushdown(y);
    if ((x && !y) || (!x && y)) {
        if (!x && y) swap(x, y), swap(lx, ly), swap(rx, ry);
        pushtag(x, p * ly + (1 - p) * ry);
        return x;
    }
    modint px = t[ls(x)].sum, py = t[ls(y)].sum, sx = t[rs(x)].sum, sy = t[rs(y)].sum;
    ls(x) = merge(ls(x), ls(y), lx, rx + sx, ly, ry + sy, p);
    rs(x) = merge(rs(x), rs(y), lx + px, rx, ly + py, ry, p);
    return pushup(x), x;
}

void dfs(int u) {
    if (!son[u][0]) {
        root[u] = init(root[u], 1, vtot, lower_bound(v0 + 1, v0 + vtot + 1, v[u]) - v0);
        return;
    } else if (!son[u][1]) {
        dfs(son[u][0]);
        root[u] = root[son[u][0]];
        return;
    }
    dfs(son[u][0]), dfs(son[u][1]);
    root[u] = merge(root[son[u][0]], root[son[u][1]], 0, 0, 0, 0, p[u]);
    return;
}

void query(int u, int i, int j) {
    if (i == j) {
        d[i] = t[u].sum;
        return;
    }
    pushdown(u);
    query(ls(u), i, M);
    query(rs(u), M + 1, j);
    return;
}

int main() {
    read(n);
    FOR(i, 1, n) {
        int fa; read(fa);
        if (fa) {
            if (!son[fa][0]) son[fa][0] = i;
            else son[fa][1] = i;
        }
    }
    FOR(i, 1, n) {
        int tmp; read(tmp);
        if (!son[i][0]) v0[++vtot] = v[i] = tmp;
        else p[i] = tmp * inv10000;
    }
    sort(v0 + 1, v0 + vtot + 1);
    dfs(1), query(root[1], 1, vtot);
    modint ans = 0;
    FOR(i, 1, vtot) ans += v0[i] * d[i] * d[i] * i;
    print(ans);
    return output(), 0;
}
}// namespace YangTY

int main() {
    YangTY::main();
    return 0;
}
