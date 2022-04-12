#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)

using namespace std;

using ll = long long;
const ll a[10] = {2, 3, 5, 7, 11, 13, 17, 19, 23};
vector<ll> ans;

ll qPow(ll base, ll exp, ll mod) {
    ll ret = 1;
    for (; exp; exp >>= 1, base = __int128(base) * base % mod)
        if (exp & 1) ret = __int128(ret) * base % mod;
    return ret;
}

bool isPrime(ll n) {
    FOR(i, 0, 8) if (a[i] == n) return true;
    if (n < 2 || !(n & 1)) return false;
    ll t = 0, u = n - 1;
    while (!(u & 1)) u >>= 1, ++t;
    FOR(i, 0, 8) {
        ll v = qPow(a[i], u, n), j;
        if (v == 1) continue;
        for (j = 1; j <= t; ++j) {
            if (v == n - 1) break;
            v = __int128(v) * v % n;
        }
        if (j > t) return false;
    }
    return true;
}

ll f(ll x, ll c, ll mod) {return (__int128(x) * x % mod + c) % mod;}
ll rnd(ll l, ll r = 0) {
    static mt19937_64 eng(20041031);
    if (l > r) swap(l, r);
    uniform_int_distribution<ll> dis(l, r);
    return dis(eng);
}

ll pollardRho(ll n) {
    ll c = rnd(1, n - 1);
    ll s = 0, t = 0, val = 1;
    int step = 0, goal = 1;
    for (goal = 1; ; goal <<= 1, s = t, val = 1) {
        for (step = 1; step <= goal; ++step) {
            t = f(t, c, n);
            val = __int128(val) * __builtin_llabs(s - t) % n;
            if (step % 127 == 0) {
                ll d = __gcd(val, n);
                if (d > 1) return d;
            }
        }
        ll d = __gcd(val, n);
        if (d > 1) return d;
    }
}

vector<ll> work(ll n) {
    if (n < 2) return {};
    if (isPrime(n)) return {n};
    ll p = n;
    while (p >= n) p = pollardRho(n);
    vector<ll> tmp = work(p), ret;
    while (n % p == 0) {
        for (auto &x : tmp) ret.emplace_back(x);
        n /= p;
    }
    tmp = work(n);
    for (auto &x : tmp) ret.emplace_back(x);
    return ret;
}

int main() {
    int T; cin >> T;
    while (T--) {
        ll n; cin >> n;
        auto ans = work(n);
        sort(ans.begin(), ans.end());
        cout << ans.size() << ' ';
        for (auto &x : ans) cout << x << ' ';
        cout << endl;
    }
    return 0;
}