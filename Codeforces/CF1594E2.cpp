#include <bits/stdc++.h>
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
};

modint qPow(modint base, modint exp) {
    base.check();
    modint ret = 1;
    for (auto p = exp.val; p; p >>= 1, base *= base)
        if (p & 1) ret *= base;
    return ret;
}

using namespace std;
using ll = long long;

map<string, int> st;
map<ll, modint> f[3];
map<ll, int> mp;
map<ll, set<ll> > G;
ll k, n;

void dfs(ll u) {
    for (auto v : G[u]) dfs(v);
    FOR(c, 0, 2) {
        if (~mp[u] && c ^ mp[u]) continue;
        f[c][u] = ~mp[u] ? 1 : 2;
        for (auto v : G[u])
            f[c][u] *= (f[(c + 1) % 3][v] + f[(c + 2) % 3][v]);
    }
    return;
}

int main() {
    ios::sync_with_stdio(false);
    cin.tie(0);
    cin >> k >> n;
    st["white"] = st["yellow"] = 0;
    st["green"] = st["blue"] = 1;
    st["red"] = st["orange"] = 2;
    FOR(i, 1, n) {
        ll u;
        string s;
        cin >> u >> s;
        mp[u] = st[s];
    }
    if (!mp.count(1)) mp[1] = -1;
    auto mp0 = mp;
    for (auto p : mp0) {
        ll u = p.first;
        while (u ^ 1) {
            G[u >> 1ll].insert(u);
            if (!mp.count(u)) mp[u] = -1;
            u >>= 1;
        }
    }
    dfs(1);
    modint ans = (f[0][1] + f[1][1] + f[2][1]) * qPow(4, ((1ll << k) - 1 - mp.size()) % (mod - 1));
    cout << ans.val << endl;
    return 0;
}
