#include <cstdio>
#include <cctype>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int mod = 1e9 + 9;

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
    
    friend modint qPow(modint base, modint exp) {
    	base.check();
    	modint ret = 1;
    	for (INT p = exp.val; p; p >>= 1, base *= base)
    		if (p & 1) ret *= base;
    	return ret;
	}
};

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

const modint coef = 276601605, base[2] = {691504013, 308495997}, inv[2] = {qPow(base[0] - 1, mod - 2), qPow(base[1] - 1, mod - 2)};
const int maxn = 3e5 + 5;
modint pow[maxn][2];

struct node {
    modint sum, tag;
} t[maxn << 2][2];

#define L (k << 1)
#define R (L | 1)
#define M ((i + j) >> 1)

void pushdown(int i, int j, int k) {
    FOR(p, 0, 1) {
        if (t[k][p].tag != 0) {
            t[L][p].tag += t[k][p].tag;
            t[R][p].tag += t[k][p].tag * pow[M - i + 1][p];
            t[L][p].sum += t[k][p].tag * inv[p] * (pow[M - i + 1][p] - 1);
            t[R][p].sum += t[k][p].tag * pow[M - i + 1][p] * inv[p] * (pow[j - M][p] - 1);
            t[k][p].tag = 0;
        }
    }
}

void pushup(int i, int j, int k) {
    FOR(p, 0, 1) t[k][p].sum = t[L][p].sum + t[R][p].sum;
    return;
}

modint query(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) return t[k][0].sum - t[k][1].sum;
    pushdown(i, j, k);
    modint ret = 0;
    if (x <= M) ret += query(i, M, L, x, y);
    if (y > M) ret += query(M + 1, j, R, x, y);
    return ret;
}

void modify(int i, int j, int k, int x, int y) {
    if (x <= i && y >= j) {
        FOR(p, 0, 1) {
            t[k][p].sum += pow[i - x + 1][p] * (pow[j - i + 1][p] - 1) * inv[p];
            t[k][p].tag += pow[i - x + 1][p];
        }
        return;
    }
    pushdown(i, j, k);
    if (x <= M) modify(i, M, L, x, y);
    if (y > M) modify(M + 1, j, R, x, y);
    pushup(i, j, k);
    return;
}

modint a[maxn];

int main() {
    int n, m; read(n), read(m);
    pow[0][0] = pow[0][1] = 1;
    FOR(i, 1, n) {
        read(a[i]), a[i] += a[i - 1];
        FOR(k, 0, 1) pow[i][k] = base[k] * pow[i - 1][k];
    }
    while (m--) {
        int op, l, r;
        read(op), read(l), read(r);
        if (op == 1) modify(1, n, 1, l, r);
        else print(coef * query(1, n, 1, l, r) + a[r] - a[l - 1], '\n');
    }
    return output(), 0;
}