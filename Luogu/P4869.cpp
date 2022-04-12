#include <bits/stdc++.h>
#define FOR(i, a, b) for (int i = (a); i <= (b); ++i)
#define DEC(i, a, b) for (int i = (a); i >= (b); --i)

using namespace std;

const int LG = 30, mod = 10086;
int p[LG + 5], n, cnt, rnk, q;

void insert(int x) {
    DEC(j, LG, 0) if ((x >> j) & 1) {
        if (!p[j]) {
            p[j] = x, ++cnt;
            break;
        } else x ^= p[j];
    }
    return;
}

int qPow(int base, int exp) {
    int ret = 1;
    for (; exp; base = 1ll * base * base % mod, exp >>= 1)
        if (exp & 1) ret = 1ll * ret * base % mod;
    return ret;
}

int main() {
    cin >> n;
    FOR(i, 1, n) {
        int x; cin >> x;
        insert(x);
    }
    cin >> q;
    vector<int> vec;
    FOR(i, 0, LG) if (p[i]) vec.push_back(i);
    FOR(i, 0, (int)vec.size() - 1) if ((q >> vec[i]) & 1) rnk += (1 << i);
    cout << (rnk % mod * qPow(2, n - cnt) % mod + 1) % mod << endl;
    return 0;
}