#include <iostream>
#include <iomanip>
#include <algorithm>
#include <vector>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;
typedef long long ll;

namespace BigInteger {
const int p = 8, carry = 1e8;

struct BigInt {
    std::vector<ll> val;
    bool neg;

    BigInt() {val.clear(), neg = 0;}
    BigInt(ll n) {
        if (n < 0) neg = 1, n = -n;
        else neg = 0;
        val.clear();
        while (n) {
            val.push_back(n % carry);
            n /= carry;
        }
    }

    il BigInt operator-() {
        BigInt ret = *this;
        ret.neg ^= 1;
        return ret;
    }

    friend istream& operator>>(istream&, BigInt&);
    friend ostream& operator<<(ostream&, BigInt);
    friend bool operator>(BigInt, BigInt);
    friend bool operator<(BigInt, BigInt);
    friend bool operator>=(BigInt, BigInt);
    friend bool operator<=(BigInt, BigInt);
    friend bool operator==(BigInt, BigInt);
    friend BigInt operator+(BigInt, BigInt);
    friend BigInt operator-(BigInt, BigInt);
    friend BigInt operator*(BigInt, BigInt);
    friend BigInt operator*(BigInt, ll);
    friend BigInt operator/(BigInt, ll);
    friend BigInt operator%(BigInt, ll);
    
    BigInt& operator+=(BigInt rhs) {return (*this) = (*this) + rhs;}
    BigInt& operator-=(BigInt rhs) {return (*this) = (*this) - rhs;}
    BigInt& operator*=(BigInt rhs) {return (*this) = (*this) * rhs;}
    BigInt& operator/=(ll rhs) {return (*this) = (*this) / rhs;}
    BigInt& operator%=(ll rhs) {return (*this) = (*this) % rhs;}
};

istream& operator>>(istream &is, BigInt &num) {
    string t; is >> t;
    reverse(t.begin(), t.end());
    if (t.back() == '-') num.neg = 1, t.pop_back();
    for (int i = 0; i < t.size(); i += p) {
        int tmp = 0;
        for (int j = i, p10 = 1; j < min(i + p, (int)t.size()); ++j, p10 *= 10)
            tmp += p10 * (t[j] - '0');
        num.val.push_back(tmp);
    }
    return is;
}

ostream& operator<<(ostream &os, BigInt num) {
    if (num.neg) os << '-';
    for (auto it = num.val.rbegin(); it != num.val.rend(); ++it)
        if (it == num.val.rbegin()) os << *it;
        else os << setw(p) << setfill('0') << *it;
    return os;
}

bool operator>(BigInt a, BigInt b) {
    if (a.neg && b.neg) return (-a) < (-b);
    if (a.neg && !b.neg) return 0;
    if (!a.neg && b.neg) return 1;
    if (a.val.size() != b.val.size()) return a.val.size() > b.val.size();
    else for (auto it1 = a.val.rbegin(), it2 = b.val.rbegin(); it1 != a.val.rend() && it2 != b.val.rend(); ++it1, ++it2)
        if (*it1 != *it2) return *it1 > *it2;
    return 0;
}

bool operator<(BigInt a, BigInt b) {
    if (a.neg && b.neg) return (-a) > (-b);
    if (a.neg && !b.neg) return 1;
    if (!a.neg && b.neg) return 0;
    if (a.val.size() != b.val.size()) return a.val.size() < b.val.size();
    for (auto it1 = a.val.rbegin(), it2 = b.val.rbegin(); it1 != a.val.rend() && it2 != b.val.rend(); ++it1, ++it2)
        if (*it1 != *it2) return *it1 < *it2;
    return 0;
}

bool operator>=(BigInt a, BigInt b) {return !(a < b);}
bool operator<=(BigInt a, BigInt b) {return !(a > b);}
bool operator==(BigInt a, BigInt b) {return a.neg == b.neg && a.val == b.val;}

BigInt operator+(BigInt a, BigInt b) {
    if (a.neg && b.neg) return -((-a) + (-b));
    if (a.neg && !b.neg) return b - (-a);
    if (!a.neg && b.neg) return a - (-b);

    BigInt ret;
    int l1 = a.val.size(), l2 = b.val.size(), l3 = max(l1, l2), tmp = 0;
    a.val.resize(l3), b.val.resize(l3), ret.val.resize(l3);
    FOR(i, 0, l3 - 1) {
        ret.val[i] = (a.val[i] + b.val[i] + tmp);
        tmp = ret.val[i] / carry;
        ret.val[i] %= carry;
    }
    while (tmp) ret.val.push_back(tmp % carry), tmp /= carry;
    return ret;
}

BigInt operator-(BigInt a, BigInt b) {
    if (a < b) return -(b - a);
    if (!a.neg && b.neg) return a + (-b);
    b.val.resize(a.val.size());
    BigInt ret;
    ret.val.resize(a.val.size());
    FOR(i, 0, (int)a.val.size() - 1) {
        ret.val[i] = a.val[i] - b.val[i];
        if (ret.val[i] < 0) {
            --a.val[i + 1];
            ret.val[i] += carry;
        }
    }
    while (ret.val.back() == 0 && ret.val.size() > 1) ret.val.pop_back();
    return ret;
}

BigInt operator*(BigInt a, BigInt b) {
    BigInt ret;
    if (a.neg ^ b.neg) ret.neg = 1;
    ret.val.resize(a.val.size() + b.val.size());
    FOR(i, 0, a.val.size() - 1) {
        FOR(j, 0, b.val.size() - 1) {
            ret.val[i + j] += a.val[i] * b.val[j];
            ret.val[i + j + 1] += ret.val[i + j] / carry;
            ret.val[i + j] %= carry;
        }
    }
    while (ret.val.back() > carry) {
        ll tmp = ret.val.back();
        ret.val.back() %= carry;
        ret.val.push_back(tmp / carry);
    }
    while (ret.val.size() > 1 && ret.val.back() == 0) ret.val.pop_back();
    return ret;
}

BigInt operator*(BigInt a, ll b) {
    bool negb = (b < 0);
    BigInt ret;
    if (a.neg ^ negb) ret.neg = 1;
    if (negb) b = -b;
    ret.val.resize(a.val.size());
    ll tmp = 0;
    FOR(i, 0, a.val.size() - 1) {
        ret.val[i] = a.val[i] * b + tmp;
        tmp = ret.val[i] / carry;
        ret.val[i] %= carry;
    }
    while (tmp > 0) {
        ret.val.push_back(tmp % carry);
        tmp /= carry;
    }
    while (ret.val.size() > 1 && ret.val.back() == 0) ret.val.pop_back();
    return ret;
}

BigInt operator/(BigInt a, ll b) {
    bool negb = (b < 0);
    BigInt ret;
    if (a.neg ^ negb) ret.neg = 1;
    if (negb) b = -b;
    ret.val.resize(a.val.size());
    ll t = 0;
    DEC(i, a.val.size() - 1, 0) {
        t = t * carry + a.val[i];
        ret.val[i] = t / b;
        t %= b;
    }
    while (ret.val.size() > 1 && ret.val.back() == 0) ret.val.pop_back();
    return ret;
}

BigInt operator%(BigInt a, ll b) {return a - a / b * b;}
}// namespace BigInteger
using BigInteger::BigInt;

int main() {
    return 0;
}