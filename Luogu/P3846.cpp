#include <cstdio>
#include <cmath>
#include <unordered_map>
#define R register
#define FOR(i, a, b) for(R int i = a; i <= b; ++i)
#define int long long

std::unordered_map<int, int> hash;

int ksm(int base, int p, int mod) {
    int ans = 1;
    for (; p; p >>= 1) {
        if (p & 1)
            ans = ans * base % mod;
        base = base * base % mod;
    }
    return ans;
}

int BSGS(int a, int b, int p) {
    hash.clear();
    if (a % p == 0)
        return -1;
    int t = ceil(sqrt(p)), val, tmp;
    hash[val = b] = 0;
    FOR(j, 1, t)
        hash[val = val * a % p] = j;
    a = ksm(a, t, p), val = 1;
    FOR(i, 1, t) {
        val = val * a % p;
        if (tmp = hash[val])
            return val = i * t - tmp, (val % p + p) % p;
    }
    return -1;
}

signed main() {
    int p, a, b;
    scanf("%lld %lld %lld", &p, &a, &b);
    int ans = BSGS(a, b, p);
    if (ans >= 0)
        return printf("%lld\n", ans), 0;
    else return printf("no solution\n"), 0;
}