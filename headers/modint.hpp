#ifndef YANGTY_MODINT_HPP
#define YANGTY_MODINT_HPP 1

#include <cassert>
#include <fastio.hpp>

namespace YangTY {

template<int mod> struct static_modint {
    using mint = static_modint;
    int val;
    inline void check() {
        val >= mod ? val %= mod : true;
        val < 0 ? (val %= mod) += mod : true;
        return;
    }
    static_modint(int v = 0) : val(v) {check();}
    inline constexpr int get_mod() {return mod;}

    inline mint &operator=(int v) {return val = v, check(), *this;}
    inline mint &operator+=(mint rhs) {return val = val + rhs.val >= mod ? val + rhs.val - mod : val + rhs.val, *this;}
    inline mint &operator-=(mint rhs) {return val = val - rhs.val < 0 ? val - rhs.val + mod : val - rhs.val, *this;}
    inline mint &operator*=(mint rhs) {return val = 1ll * val * rhs.val % mod, *this;}

    inline friend mint operator+(const mint &lhs, const mint &rhs) {return mint(lhs) += rhs;}
    inline friend mint operator-(const mint &lhs, const mint &rhs) {return mint(lhs) -= rhs;}
    inline friend mint operator*(const mint &lhs, const mint &rhs) {return mint(lhs) *= rhs;}
    inline friend bool operator==(const mint &lhs, const mint &rhs) {return lhs.val == rhs.val;}
    inline friend bool operator!=(const mint &lhs, const mint &rhs) {return lhs.val != rhs.val;}
    inline friend bool operator>(const mint &lhs, const mint &rhs) {return lhs.val > rhs.val;}
    inline friend bool operator<(const mint &lhs, const mint &rhs) {return lhs.val < rhs.val;}
    inline friend bool operator>=(const mint &lhs, const mint &rhs) {return lhs.val >= rhs.val;}
    inline friend bool operator<=(const mint &lhs, const mint &rhs) {return lhs.val <= rhs.val;}

    inline mint &operator++() {
        ++val;
        if (val == mod) val = 0;
        return *this;
    }
    inline mint &operator--() {
        if (val == 0) val = mod;
        --val;
        return *this;
    }
    inline mint operator++(int) {
        mint ret = *this;
        ++*this;
        return ret;
    }
    inline mint operator--(int) {
        mint ret = *this;
        --*this;
        return ret;
    }

    inline mint operator+() const {return *this;}
    inline mint operator-() const {return mint() - *this;}
};

/*
struct dynamic_modint {
    using mint = dynamic_modint;
    int mod, val;
    inline void check() {
        val >= mod ? val %= mod : true;
        val < 0 ? (val %= mod) += mod : true;
        return;
    }
    void set_mod(int M) {
        static int cnt;
        mod = M, ++cnt;
        assert(cnt == 1);
        return;
    }
    dynamic_modint(int v = 0) : mod(998244353), val(v) {check();}

    inline mint &operator=(int v) {return val = v, check(), *this;}
    inline mint &operator+=(mint rhs) {return val = val + rhs.val >= mod ? val + rhs.val - mod : val + rhs.val, *this;}
    inline mint &operator-=(mint rhs) {return val = val - rhs.val < 0 ? val - rhs.val + mod : val - rhs.val, *this;}
    inline mint &operator*=(mint rhs) {return val = 1ll * val * rhs.val % mod, *this;}

    inline friend mint operator+(const mint &lhs, const mint &rhs) {return mint(lhs) += rhs;}
    inline friend mint operator-(const mint &lhs, const mint &rhs) {return mint(lhs) -= rhs;}
    inline friend mint operator*(const mint &lhs, const mint &rhs) {return mint(lhs) *= rhs;}
    inline friend bool operator==(const mint &lhs, const mint &rhs) {return lhs.val == rhs.val;}
    inline friend bool operator!=(const mint &lhs, const mint &rhs) {return lhs.val != rhs.val;}
    inline friend bool operator>(const mint &lhs, const mint &rhs) {return lhs.val > rhs.val;}
    inline friend bool operator<(const mint &lhs, const mint &rhs) {return lhs.val < rhs.val;}
    inline friend bool operator>=(const mint &lhs, const mint &rhs) {return lhs.val >= rhs.val;}
    inline friend bool operator<=(const mint &lhs, const mint &rhs) {return lhs.val <= rhs.val;}

    inline mint &operator++() {
        ++val;
        if (val == mod) val = 0;
        return *this;
    }
    inline mint &operator--() {
        if (val == 0) val = mod;
        --val;
        return *this;
    }
    inline mint operator++(int) {
        mint ret = *this;
        ++*this;
        return ret;
    }
    inline mint operator--(int) {
        mint ret = *this;
        --*this;
        return ret;
    }

    inline mint operator+() const {return *this;}
    inline mint operator-() const {return mint() - *this;}
};
*/

using modint998244353 = static_modint<998244353>;
using modint1000000007 = static_modint<1000000007>;
// using modint = dynamic_modint;

namespace fastIO {

template<int mod> ostream& operator<<(ostream &out, static_modint<mod> x) {
    out << x.val;
    return out;
}

/*
ostream& operator<<(ostream &out, dynamic_modint x) {
    out << x.val;
    return out;
}
*/

} // namespace fastIO

} // namespace YangTY

#endif // YANGTY_MODINT_HPP