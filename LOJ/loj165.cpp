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
template<typename T> void print(T x) {
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
void output() {fwrite(obuf, __pO - obuf, 1, stdout);}
}

using namespace fastIO;

const int maxn = 3005;
modint g = 1, w[maxn], x[maxn], y[maxn];
int cnt;

void ins(int cnt) {
    w[cnt] = y[cnt];
    FOR(i, 1, cnt - 1) w[i] *= qPow(x[i] - x[cnt], mod - 2), w[cnt] *= qPow(x[cnt] - x[i], mod - 2);
    return;
}

modint calc(modint k) {
    FOR(i, 1, cnt) if (k == x[i]) return y[i];
    modint g = 1;
    FOR(i, 1, cnt) g *= (k - x[i]);
    modint ret = 0;
    FOR(i, 1, cnt) ret += w[i] * qPow(k - x[i], mod - 2);
    return ret * g;
}

int main() {
    int n; read(n);
    while (n--) {
        int op;
        read(op);
        if (op == 1) {
            read(x[++cnt]), read(y[cnt]);
            ins(cnt);
        } else {
            int x; read(x);
            print(calc(x));
            putchar('\n');
        }
    }
    return output(), 0;
}
