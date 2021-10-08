#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

int mod = 1;

struct modint {
    int val;
    il void check() {
        val >= mod ? val %= mod : true;
        val < 0 ? (val %= mod) += mod : true;
        return;
    }
    modint(int v = 0) : val(v) {check();}

    il modint &operator=(int v) {return val = v, *this;}
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

using namespace fastIO;

int n, Sr, Sb, Sg, m, tr[65], sz[65], vis[65];
modint f[65][65][65];

modint calc() {
    int tot = 0;
    FOR(i, 0, Sr) FOR(j, 0, Sb) FOR(k, 0, Sg) f[i][j][k] = 0;
    FOR(i, 1, n) vis[i] = 0;
    for (int i = 1, p, len; i <= n; ++i) {
        if (vis[i]) continue;
        len = 0, p = i;
        while (!vis[p]) {
            vis[p] = 1;
            ++len;
            p = tr[p];
        }
        sz[++tot] = len;
    }
    f[0][0][0] = 1;
    FOR(i, 1, tot) {
        DEC(nr, Sr, 0) {
            DEC(nb, Sb, 0) {
                DEC(ng, Sg, 0) {
                    if (nr >= sz[i]) f[nr][nb][ng] += f[nr - sz[i]][nb][ng];
                    if (nb >= sz[i]) f[nr][nb][ng] += f[nr][nb - sz[i]][ng];
                    if (ng >= sz[i]) f[nr][nb][ng] += f[nr][nb][ng - sz[i]];
                }
            }
        }
    }
    return f[Sr][Sb][Sg];
}

int main() {
    read(Sr), read(Sb), read(Sg), read(m), read(mod);
    modint ans = 0;
    n = Sr + Sb + Sg;
    bool flag = 0;
    FOR(i, 1, m) {
        bool tmp = 1;
        FOR(j, 1, n) read(tr[j]), tmp &= (tr[j] == j);
        ans += calc(), flag |= tmp;
    }
    if (!flag) {
        FOR(j, 1, n) tr[j] = j;
        ans += calc();
    }
    print(ans * qPow(m + (!flag), mod - 2));
    return output(), 0;
}