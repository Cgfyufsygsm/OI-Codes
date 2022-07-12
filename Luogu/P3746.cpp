#include <bits/stdc++.h>
#define il inline
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define szof(a) ((int) (a).size())

using namespace std;
using Poly = vector<int>;
int n, mod, k, r;

il void add(int &x, int y) {x += y, x >= mod ? x -= mod : (0-0);}

Poly operator*(const Poly &a, const Poly &b) {
    Poly c(k);
    FOR(i, 0, szof(a) - 1) FOR(j, 0, szof(b) - 1) add(c[(i + j) % k], 1ll * a[i] * b[j] % mod);
    return c;
}

int main() {
    cin >> n >> mod >> k >> r;
    Poly ret = {1}, f = {1, 1};
    for (long long exp = 1ll * n * k; exp; exp >>= 1, f = f * f)
        if (exp & 1) ret = ret * f;
    cout << ret[r] << endl;
    return 0;
}