#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;
using ll = long long;
const ll a[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23};

ll qPow(ll base, ll exp, ll mod) {
    ll ret = 1;
    for (; exp; exp >>= 1, base = __int128(base) * base % mod)
        if (exp & 1) ret = __int128(ret) * base % mod;
    return ret;
}

bool isPrime(ll n) {
    FOR(i, 0, 8) if (n == a[i]) return true;
    if (n < 2 || !(n & 1)) return false;
    ll t = 0, u = n - 1, j;
    while (!(u & 1)) u >>= 1, ++t;
    FOR(i, 0, 8) {
        ll v = qPow(a[i], u, n);
        if (v == 1) continue;
        for (j = 1; j <= t; ++j) {
            if (v == n - 1) break;
            v = __int128(v) * v % n;
        }
        if (j > t) return false;
    }
    return true;
}

int main() {
    ll x;
    while (cin >> x) puts(isPrime(x) ? "Y" : "N");
    return 0;
}