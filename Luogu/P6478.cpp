#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int mod = 998244353;

struct modint {
    typedef int INT;
    static const INT mod = ::mod;
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
void print(modint x) {
    print(x.val);
}
template<typename T> il void print(const T &x, const char &c) {print(x), putchar(c);}
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

template<typename T> il T min(const T &a, const T &b) {return a < b ? a : b;}

using namespace fastIO;

const int maxn = 5005;
int n, head[maxn], to[maxn << 1], nxt[maxn << 1], cnte;
int size[maxn], cnt1[maxn];
char str[maxn];
modint f[maxn][maxn], tmp[maxn], fac[maxn], invfac[maxn];

modint binom(int n, int m) {return n < m ? 0 : fac[n] * invfac[m] * invfac[n - m];}

il void add(int u, int v) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    head[u] = cnte;
    return;
}

void dfs(int u, int fa) {
    size[u] = 1, cnt1[u] = str[u] - '0';
    f[u][0] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int &v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        FOR(j, 0, (size[u] + size[v]) >> 1) tmp[j] = 0;
        FOR(j, 0, size[u] >> 1)
            FOR(k, 0, size[v] >> 1)
                tmp[j + k] += f[u][j] * f[v][k];
        FOR(j, 0, (size[u] + size[v]) >> 1) f[u][j] = tmp[j];
        size[u] += size[v], cnt1[u] += cnt1[v];
    }
    DEC(i, min(cnt1[u], size[u] - cnt1[u]), 1) {
        if (str[u] == '1') f[u][i] += f[u][i - 1] * (size[u] - cnt1[u] - (i - 1));
        else f[u][i] += f[u][i - 1] * (cnt1[u] - (i - 1));
    }
    return;
}

int main() {
    fac[0] = 1;
    FOR(i, 1, 5000) fac[i] = fac[i - 1] * i;
    invfac[5000] = qPow(fac[5000], mod - 2);
    DEC(i, 4999, 0) invfac[i] = (i + 1) * invfac[i + 1];
    read(n);
    read(str + 1);
    FOR(i, 1, n - 1) {
        int u, v; read(u), read(v);
        add(u, v), add(v, u);
    }
    dfs(1, 0);
    FOR(k, 0, n >> 1) {
        modint res = 0;
        FOR(i, k, n >> 1) {
            modint tmp = binom(i, k) * f[1][i] * fac[n / 2 - i];
            if ((i - k) & 1) res -= tmp;
            else res += tmp;
        }
        print(res, '\n');
    }
    return output(), 0;
}