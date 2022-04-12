#include <bits/stdc++.h>
#include <atcoder/modint>
using namespace std;
using mint = atcoder::modint1000000007;
unordered_map<int, mint> F;
int n, m;
mint inv;

mint getF(int m) {
    if (F.count(m)) return F[m];
    mint ret = n;
    for (int l = 2, r; l <= n; l = r + 1) {
        if (m / l == 0) break;
        r = min(n, m / (m / l));
        ret += getF(m / l) * (r - l + 1);
    }
    return F[m] = ret * inv;
}

int main() {
    cin >> n >> m;
    F[0] = 1, inv = mint(n - 1).inv();
    cout << getF(m).val() << endl;
    return 0;
}