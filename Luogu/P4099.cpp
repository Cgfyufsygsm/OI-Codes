#include <cstdio>
#include <cstring>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

const int mod = 1e9 + 7;

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

const int maxn = 1005;
modint binom[maxn][maxn];
int n, head[maxn], to[maxn << 1], nxt[maxn << 1], w[maxn << 1], cnte, size[maxn];
modint f[maxn][maxn], g[maxn];

il void add(int u, int v, int _w) {
    to[++cnte] = v;
    nxt[cnte] = head[u];
    w[cnte] = _w;
    head[u] = cnte;
    return;
}

void dfs(int u, int fa) {
    f[u][1] = size[u] = 1;
    for (int i = head[u]; i; i = nxt[i]) {
        int v = to[i];
        if (v == fa) continue;
        dfs(v, u);
        memcpy(g, f[u], sizeof g);
        memset(f[u], 0, sizeof f[u]);
        if (w[i])
            FOR(k1, 1, size[u])
                FOR(k, k1, k1 + size[v] - 1)
                    f[u][k] += g[k1] * (f[v][size[v]] - f[v][k - k1]) * binom[k - 1][k1 - 1] * binom[size[u] + size[v] - k][size[u] - k1];
        else FOR(k1, 1, size[u])
            FOR(k, k1 + 1, size[u] + size[v])
                f[u][k] += g[k1] * f[v][k - k1] * binom[k - 1][k1 - 1] * binom[size[u] + size[v] - k][size[u] - k1];
        size[u] += size[v];
    }
    FOR(i, 1, size[u]) f[u][i] += f[u][i - 1];
    return;
}

int main() {
    binom[0][0] = binom[1][0] = binom[1][1] = 1;
    FOR(i, 2, 1000) {
        binom[i][0] = binom[i][i] = 1;
        FOR(j, 1, i - 1) binom[i][j] = binom[i - 1][j] + binom[i - 1][j - 1];
    }
    int T; scanf("%d", &T);
    while (T--) {
        memset(head, 0, sizeof head), cnte = 0;
        scanf("%d", &n);
        FOR(i, 1, n - 1) {
            int u, v;
            char ch;
            scanf("%d %c %d", &u, &ch, &v);
            ++u, ++v;
            add(u, v, ch == '<');
            add(v, u, ch == '>');
        }
        dfs(1, 0);
        printf("%d\n", f[1][n].val);
    }
    return 0;
}
